#ifndef __POSTCMDEX_H__
#define __POSTCMDEX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <vector>
#include <typeinfo>
#include <exception>
#include <algorithm>
#include <cassert>

//#include "boost/shared_ptr.hpp"

//#include "BaseCode/BaseFunc.h"
//#include "BaseCode/PostCmdDefine.h"
#define CHECK
#define DWORD			unsigned int
#define WPARAM			unsigned short
#define LPARAM			unsigned short

unsigned int GetCurrentThreadId()
{
	static unsigned int i = 1235;
//	return ++i;
	return i;
}

void DebugMsg(...) {;}

namespace postcmdex
{
//	using std::tr1::shared_ptr;
	using std::shared_ptr;

	// =============================================================================================================
	//    class cannot_copy
	//    从这个类继承出的类将无法实现复制（copy construct, operator =）
	//    请使用private继承
	// =============================================================================================================
	class cannot_copy
	{
	protected:
		cannot_copy()
		{
		}
		~cannot_copy()
		{
		}
	private:
		cannot_copy(const cannot_copy&);			// will never be implemented
		cannot_copy& operator=(const cannot_copy&);	// will never be implemented
	};

	// =============================================================================================================
	//    class virtual_destructor
	//    从这个类继承出的类，其析构函数是virtual的
	//    请使用private继承
	// =============================================================================================================
	class virtual_destructor
	{
	protected:
		virtual ~virtual_destructor()
		{
		}
	};
}

// =================================================================================================================
//    使用#define POSTCMDEX_USE_BOOST
//    any, any_cast, bad_any_cast, reference_wrapper, ref, cref, functype等都使用boost实现
// =================================================================================================================
#ifdef POSTCMDEX_USE_BOOST
#include <boost/any.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>
namespace postcmdex
{
	using boost::any;
	using boost::any_cast;
	using boost::bad_any_cast;
	using boost::reference_wrapper;
	using boost::ref;
	using boost::cref;
	typedef typename boost::function0<void> functype;
}
#else  // #ifdef POSTCMDEX_USE_BOOST
// =================================================================================================================
//    未使用#define POSTCMDEX_USE_BOOST
//    any, any_cast, bad_any_cast, reference_wrapper, ref, cref, functype等都使用自己实现
// =================================================================================================================
namespace postcmdex
{
	// =============================================================================================================
	//    template class reference_wrapper
	//    一个可以包裹引用的数据类型。可以隐式的转换为C++内建的引用类型。
	// =============================================================================================================
	template <typename T>
	class reference_wrapper
	{
	public:
		explicit reference_wrapper(T& t)
			: m_rt(t)
		{
		}

		operator T&() const
		{
			return m_rt;
		}

	private:
		T& m_rt;
	};

	// =============================================================================================================
	//    template function ref<T>
	//    template function cref<T>
	//    这两个函数用于产生reference_wrapper对象。
	//    优势是不必指定模板参数，由编译器自动判断。比如ref(i)就比reference_wrapper<int>(i)简洁。
	// =============================================================================================================
	template <typename T>
	reference_wrapper<T> ref(T& t)
	{
		return reference_wrapper<T>(t);
	}

	template <typename T>
	reference_wrapper<const T> cref(const T& t)
	{
		return reference_wrapper<const T>(t);
	}

	// =============================================================================================================
	//    class any
	//    一个可以包裹任意数据的数据类型
	//    实现时需要any_holder_base和any_holder<T>的支持
	// =============================================================================================================
	class any_holder_base : private cannot_copy, private virtual_destructor
	{
	public:
		virtual const type_info& type() const = 0;
		virtual const void* content_ptr() const = 0;
	};

	template <typename T>
	class any_holder : public any_holder_base
	{
	public:
		any_holder(const T& content)
			: m_content(content)
		{
		}

		virtual const type_info& type() const
		{
			return typeid(T);
		}

		virtual const void* content_ptr() const
		{
			return &m_content;
		}

	private:
		const T m_content;
	};

	class any
	{
	public:
		any()
		{
		}

		template <typename T>
		any(const T& t)
			: m_pHolder(new any_holder<T>(t))
		{
		}

		template <typename T>
		any& operator=(const T& t)
		{
			m_pHolder.reset(new any_holder<T>(t));
			return *this;
		}

		bool empty() const
		{
			return m_pHolder.get() == 0;
		}

		const type_info& type() const
		{
			if (empty()) {
				return typeid(void);
			}

			return m_pHolder->type();
		}

		template <typename T>
		friend const T any_cast(const any& obj);

	private:
		shared_ptr<any_holder_base> m_pHolder;
	};

	// =============================================================================================================
	//    class bad_any_cast
	//    当any_cast失败时产生的异常
	// =============================================================================================================
	class bad_any_cast : public std::bad_cast
	{
	public:
		virtual const char* what() const
		{
			return "bad any cast";
		}
	};

	// =============================================================================================================
	//    template function any_cast
	//    把由any包裹的数据转化为普通数据。转化失败会产生bad_any_cast异常
	// =============================================================================================================
	template <typename T>
	const T any_cast(const any& obj)
	{
		if (obj.type() != typeid(T)) {
			throw bad_any_cast();
		}

		return *static_cast<const T*>(obj.m_pHolder->content_ptr());
	}

	// =============================================================================================================
	//    class functype
	//    一种可以包裹各种“可调用物”（即：函数指针或者函数对象）的数据类型。
	//    这里只需要支持“无参数，返回类型为void”的可调用物。
	//    实现时需要func_holder_base和func_holder<F>的支持
	// =============================================================================================================
	class func_holder_base : private cannot_copy, private virtual_destructor
	{
	public:
		virtual void call() const = 0;
	};

	template <typename F>
	class func_holder : public func_holder_base
	{
	public:
		func_holder(const F& f)
			: m_f(f)
		{
		}

		virtual void call() const
		{
			m_f();
		}

	private:
		F m_f;
	};

	class functype
	{
	public:
		template <typename F>
		functype(const F& f)
			: m_pHolder(new func_holder<F>(f))
		{
		}

		void operator()(void) const
		{
			CHECK(m_pHolder);

			m_pHolder->call();
		}

	private:
		shared_ptr<func_holder_base> m_pHolder;
	};

} // end of namespace postcmdex
#endif // #ifdef POSTCMDEX_USE_BOOST

namespace postcmdex
{
	// =============================================================================================================
	//    struct CmdInfo
	//    容纳了一次PostCmdEx时所传入的各种信息
	//    主要成员为m_Argument，指PostCmdEx时传入的参数
	//    如果是_DEBUG版本，则还包括了m_szPosterFile和m_nPosterLine两个成员，分别表示了PostCmd之时的__FILE__和__LINE__
	// =============================================================================================================
	struct CmdInfo
	{
		any				m_Argument;
		const char*		m_szPosterFile;
		int				m_nPosterLine;

		template <typename T>
		CmdInfo(const T& arg)
			: m_Argument(arg)
			, m_szPosterFile(0)
			, m_nPosterLine(0)
		{
		}
	};

	// =============================================================================================================
	//    class CmdState
	//    保存“当前状态”，保证线程独立性。
	//    对每个线程而言，它是单件模式实现的。
	// =============================================================================================================
	class CmdState : private cannot_copy
	{
	public:
		static CmdState& GetInstance()
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static std::map<DWORD, shared_ptr<CmdState> > s_mapInstance;
			DWORD idThread = GetCurrentThreadId();
			shared_ptr<CmdState>& pInstance = s_mapInstance[idThread];
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if (!pInstance) {
				pInstance.reset(new CmdState);
			}

			return *pInstance;
		}

		DWORD GetCurrentCommand() const
		{
			assert(m_dwCurrentCommand != 0);

			return m_dwCurrentCommand;
		}

		const CmdInfo& GetCurrentInfo() const
		{
			assert(m_pCurrentInfo != 0);

			return *m_pCurrentInfo;
		}

		friend class CmdStateGuard;

	private:
		DWORD			m_dwCurrentCommand;
		const CmdInfo*	m_pCurrentInfo;

		CmdState()
			: m_dwCurrentCommand(0)
			, m_pCurrentInfo(0)
		{
		}
	};

	// =============================================================================================================
	//    class CmdStateGuard
	//    对CmdState的包装
	//    在析构函数中清除状态
	// =============================================================================================================
	class CmdStateGuard
	{
	public:
		CmdStateGuard()
		{
		}

		~CmdStateGuard()
		{
			SetState(0, 0);
		}

		void SetState(DWORD dwCommand, const CmdInfo* pInfo)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CmdState& rCmdState = CmdState::GetInstance();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			rCmdState.m_dwCurrentCommand = dwCommand;
			rCmdState.m_pCurrentInfo = pInfo;
		}
	};

	// =============================================================================================================
	//    struct FirstLess
	//    一个function object，比较两个std::pair<int, functype>的大小。用于对func进行排序
	// =============================================================================================================
	struct PriorityLess
	{
		bool operator()(const std::pair<int, functype>& a, const std::pair<int, functype>& b) const
		{
			return a.first < b.first;
		}
	};

	// =============================================================================================================
	//    class CmdMgr
	//    核心实现类。使用单件模式实现。
	// =============================================================================================================
	class CmdMgr : private cannot_copy
	{
	public:
		static CmdMgr& GetInstance()
		{
			//~~~~~~~~~~~~~~~~~~~~~~
			static CmdMgr s_instance;
			//~~~~~~~~~~~~~~~~~~~~~~

			return s_instance;
		}

		template <typename F>
		void AddListener(DWORD dwCommand, const F& f, int priority = 0)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			std::vector<std::pair<int, functype> >& vecListeners = m_mapListeners[dwCommand];
			functype fun = f;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			vecListeners.insert(
				std::upper_bound(vecListeners.begin(), vecListeners.end(), std::make_pair(priority, fun), PriorityLess()),
				std::make_pair(priority, fun)
				);
		}

		void DoDispatchMessage(WPARAM wParam, LPARAM lParam)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			DWORD dwCurrentCommand = static_cast<DWORD>(wParam);

			std::map<LPARAM, CmdInfo>::iterator itInfo = m_mapInfo.find(lParam);
			shared_ptr<CmdInfo> pInfo;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if (itInfo != m_mapInfo.end()) {
				pInfo.reset(new CmdInfo((*itInfo).second));
				m_mapInfo.erase(itInfo);
			} else {
				DebugMsg(
					"消息编号：%u\n"
					"\t没有找到关于该消息的任何参数",
					dwCurrentCommand
					);
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CmdStateGuard objStateGuard;
			objStateGuard.SetState(dwCurrentCommand, pInfo.get());

			std::map<DWORD, std::vector<std::pair<int, functype> > >::iterator
				itListeners = m_mapListeners.find(dwCurrentCommand);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if (itListeners == m_mapListeners.end()) {
				DebugMsg(
					"消息编号：%u\n"
					"\t没有找到关于该消息的任何回调函数",
					dwCurrentCommand
					);
				return;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			std::vector<std::pair<int, functype> >& vecListeners = (*itListeners).second;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			for(std::vector<std::pair<int, functype> >::iterator
				it = vecListeners.begin(); it != vecListeners.end(); ++it) {
				try {
					((*it).second)();
				} catch (bad_any_cast&) {
					// eat the exception
				}
			}
		}

		template <typename T>
		void Post(DWORD dwCommand, const T& data, bool bSyncCall = false)
		{
// 			if (!g_hGameWnd) {
// 				return;
// 			}

			Post__(dwCommand, CmdInfo(data), bSyncCall);
		}

		template <typename T>
		void Post_dbg(DWORD dwCommand, const T& data, const char* szFile, int nLine, bool bSyncCall = false)
		{
// 			if (!g_hGameWnd) {
// 				return;
// 			}

			CmdInfo info(data);
			info.m_szPosterFile = szFile;
			info.m_nPosterLine = nLine;

			Post__(dwCommand, info, bSyncCall);
		}

#ifdef _DEBUG
		~CmdMgr()
		{
			if (!m_mapInfo.empty()) {
				DebugMsg("程序结束之时还有尚未被响应的消息");

				for(std::map<LPARAM, CmdInfo>::iterator
					it = m_mapInfo.begin(); it != m_mapInfo.end(); ++it) {

					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					const CmdInfo& info = (*it).second;
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					DebugMsg(
						"消息编号：%u\n"
						"\t位置：%s(%d)\n"
						"\t参数类型：%s",
						(*it).first, info.m_szPosterFile, info.m_nPosterLine, info.m_Argument.type().name()
						);
				}
			}
		}
#endif

	private:
		std::map<LPARAM, CmdInfo>									m_mapInfo;
		std::map<DWORD, std::vector<std::pair<int, functype> > >	m_mapListeners;

		LPARAM genID()
		{
			//~~~~~~~~~~~~~~~~~~
			static LPARAM id = 0;
			//~~~~~~~~~~~~~~~~~~

			do {
				++id;
			} while (m_mapInfo.find(id) != m_mapInfo.end());

			return id;
		}

		void Post__(DWORD dwCommand, const CmdInfo& info, bool bSyncCall)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			LPARAM id = genID();
			bool bInsertSuccess = m_mapInfo.insert(std::make_pair(id, info)).second;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			CHECK(bInsertSuccess);

			//#hy:
			DoDispatchMessage(dwCommand, id);
// 			if (bSyncCall) {
// 				::SendMessage(g_hGameWnd, WM_MY_MESSAGE_EX, dwCommand, id);
// 			} else {
// 				::PostMessage(g_hGameWnd, WM_MY_MESSAGE_EX, dwCommand, id);
// 			}
		}
	}; // end of class CmdMgr

	// =============================================================================================================
	//    function nothing
	// =============================================================================================================
	class nothing_t
	{
	};

	inline nothing_t nothing()
	{
		return nothing_t();
	}

} // end of namespace postcmdex

// =================================================================================================================
//    实用宏/实用全局函数
//    g_objCmdMgr
//    g_objCmdState
//    PostCmdEx
//    SendCmdEx
//    PostCmdEx0
//    SendCmdEx0
//    GetCurrentArg
//    GetCurrentArgRef
//    GetCurrentArgCRef
// =================================================================================================================
#define g_objCmdMgr				(postcmdex::CmdMgr::GetInstance())
#define g_objCmdState			(postcmdex::CmdState::GetInstance())

// 包含窗体多实例信息的CMD
#define MAKE_INSTANCE_CMD(usInstanceIndex, usCmd) ((static_cast<UINT>(usInstanceIndex) << 16) + static_cast<USHORT>(usCmd))

#ifdef _DEBUG
#define PostCmdEx(dwCommand, data)		(g_objCmdMgr.Post_dbg((dwCommand), (data), __FILE__, __LINE__))
#define SendCmdEx(dwCommand, data)		(g_objCmdMgr.Post_dbg((dwCommand), (data), __FILE__, __LINE__, true))
#else
#define PostCmdEx(dwCommand, data)		(g_objCmdMgr.Post((dwCommand), (data)))
#define SendCmdEx(dwCommand, data)		(g_objCmdMgr.Post((dwCommand), (data), true))
#endif
#define PostCmdEx0(dwCommand)			(PostCmdEx((dwCommand), postcmdex::nothing()))
#define SendCmdEx0(dwCommand)			(SendCmdEx((dwCommand), postcmdex::nothing()))

template <typename T>
T GetCurrentArg()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const postcmdex::CmdInfo& info = g_objCmdState.GetCurrentInfo();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef _DEBUG
	try {
		return postcmdex::any_cast<T>(info.m_Argument);
	} catch (postcmdex::bad_any_cast&) {
		char szMessage[4096] = {0};
// 		_snprintf(szMessage, sizeof(szMessage),
// 			"--- GetCurrentArg 参数类型不匹配 ---\n"
// 			"消息编号：%u\n"
// 			"位置：%s(%d)\n"
// 			"在PostCmdEx中传入参数类型为%s\n"
// 			"在GetCurrentArg中请求取得的参数类型为%s",
// 			g_objCmdState.GetCurrentCommand(),
// 			info.m_szPosterFile,
// 			info.m_nPosterLine,
// 			info.m_Argument.type().name(), typeid(T).name()
// 			);
		szMessage[sizeof(szMessage) - 1] = '\0';
//		MessageBoxA(g_hGameWnd, szMessage, "", MB_ICONEXCLAMATION);
		throw;
	}
#else
	return postcmdex::any_cast<T>(info.m_Argument);
#endif
}

template <typename T>
T& GetCurrentArgRef()
{
	postcmdex::reference_wrapper<T> r = GetCurrentArg<postcmdex::reference_wrapper<T> >();
	return r;
}

template <typename T>
const T& GetCurrentArgCRef()
{
	postcmdex::reference_wrapper<const T> r = GetCurrentArg<postcmdex::reference_wrapper<const T> >();
	return r;
}

//#include "BaseCode/PostCmdExFunctional.h"
#include "PostCmdExFunctional.h"

#endif

