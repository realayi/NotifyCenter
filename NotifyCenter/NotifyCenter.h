#ifndef __NOTIFYCENTER_H__
#define __NOTIFYCENTER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <typeinfo>
#include <exception>

namespace NC	//notify center
{
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

namespace NC	//notify center
{
	// =================================================================================================================
	//    reference_wrapper, shared_ptr, functype, binder 等都可以使用c++11实现
	//    cocos2d-x 2.x不原生支持c++11,都使用自己实现
	// =================================================================================================================

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

	// STRUCT _Nil
	struct _Nil
	{	// empty struct, for unused argument types
	};
	static _Nil _Nil_obj;

	// TEMPLATE CLASS integral_constant
	template<class _Ty,
		_Ty _Val>
	struct integral_constant
	{	// convenient template for integral constant types
		static const _Ty value = _Val;

		typedef _Ty value_type;
		typedef integral_constant<_Ty, _Val> type;

		operator value_type() const
		{	// return stored value
			return (value);
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// TEMPLATE CLASS is_same
	template<class _Ty1, class _Ty2>
	struct is_same
		: false_type
	{	// determine whether _Ty1 and _Ty2 are the same type
	};

	template<class _Ty1>
	struct is_same<_Ty1, _Ty1>
		: true_type
	{	// determine whether _Ty1 and _Ty2 are the same type
	};

	// TEMPLATE CLASS _Is_reference_wrapper
	template<class _Barg>
	struct _Is_reference_wrapper
		: false_type
	{	// false in general
	};

	template<class _Barg>
	struct _Is_reference_wrapper<reference_wrapper<_Barg> >
		: true_type
	{	// true if reference wrapper
	};

	// =============================================================================================================
	//    class shared_ptr
	//    引用计数的智能指针
	// =============================================================================================================
	template<class T>
	class shared_ptr
	{
		struct aux
		{
			unsigned count;

			aux() :count(1) {}
			virtual void destroy()=0;
			virtual ~aux() {} //must be polymorphic
		};

		template<class U, class Deleter>
		struct auximpl: public aux
		{
			U* p;
			Deleter d;

			auximpl(U* pu, const Deleter& x)
			{
				p = pu;
				d = x;
			}
			virtual void destroy() { d(p); } 
		};

		template<class U>
		struct default_deleter
		{
			void operator()(U* p) const { delete p; }
		};

		aux* pa;
		T* pt;
		
		void inc() { if(pa) (++pa->count); }

		void dec() 
		{ 
			if(pa && !(--pa->count)) 
			{  pa->destroy(); delete pa; }
		}

	public:

		shared_ptr() :pa(), pt() {}

		template<class U, class Deleter>
		shared_ptr(U* pu, Deleter d) :pa(new auximpl<U,Deleter>(pu,d)), pt(pu) {}

		template<class U>
		explicit shared_ptr(U* pu) :pa(new auximpl<U,default_deleter<U> >(pu,default_deleter<U>())), pt(pu) {}

		shared_ptr(const shared_ptr& s) :pa(s.pa), pt(s.pt) { inc(); }

		template<class U>
		shared_ptr(const shared_ptr<U>& s) :pa(s.pa), pt(s.pt) { inc(); }

		~shared_ptr() { dec(); }

		shared_ptr& operator=(const shared_ptr& s)
		{
			if(this!=&s)
			{
				dec();
				pa = s.pa; pt=s.pt;
				inc();
			}        
			return *this;
		}

		T* get() const { return pt; }
		T* operator->() const { return pt; }
		T& operator*() const { return *pt; }
	};

	// =============================================================================================================
	//    class any
	//    一个可以包裹任意数据的数据类型
	//    实现时需要any_holder_base和any_holder<T>的支持
	// =============================================================================================================
	class any_holder_base : private cannot_copy, private virtual_destructor
	{
	public:
		virtual const std::type_info& type() const = 0;
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

		virtual const std::type_info& type() const
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
			if(this!=&t)
			{
				m_pHolder = t.m_pHolder;
			}

			return *this;
		}

		bool empty() const
		{
			return m_pHolder.get() == 0;
		}

		const std::type_info& type() const
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
		virtual const char* what() const throw()
		{
			return "bad any cast";
		}
	};

	// =============================================================================================================
	//    template struct Fixarg_ret
	//    将reference_wrapper转为具体的类型
	// =============================================================================================================
	template<class _Barg>
	struct Fixarg_ret
	{	// false in general
		typedef _Barg type;
	};

	template<class _Barg>
	struct Fixarg_ret<reference_wrapper<_Barg> >
	{	// true if reference wrapper
		typedef _Barg type;
	};

	// =============================================================================================================
	//    template function any_cast
	//    把由any包裹的数据转化为普通数据。转化失败会产生bad_any_cast异常
	// =============================================================================================================
	template <typename T>
	const T any_cast(const any& obj)
	{
		if (_Is_reference_wrapper<T>::value)
		{
			if (obj.type() != typeid(typename Fixarg_ret<T>::type)) {
				throw bad_any_cast();
			}

			typedef typename Fixarg_ret<T>::type base_type;
			const base_type* baseValue = static_cast<const base_type*>(obj.m_pHolder->content_ptr());
			base_type* no_const = const_cast<base_type*>(baseValue);
			return reference_wrapper<base_type>(*no_const);
		}
		else
		{
			if (obj.type() != typeid(T)) {
				throw bad_any_cast();
			}
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
			m_pHolder->call();
		}

	private:
		shared_ptr<func_holder_base> m_pHolder;
	};
};

namespace NC
{
	// =============================================================================================================
	//    struct CmdInfo
	//    容纳了一次Notify时所传入的各种信息
	//    主要成员为m_Argument，指Notify时传入的参数
	//    如果是_DEBUG版本，则还包括了m_szPosterFile和m_nPosterLine两个成员，分别表示了Notify之时的__FILE__和__LINE__
	// =============================================================================================================
	struct CmdInfo
	{
		std::vector<any>	m_Argument;
		const char*			m_szPosterFile;
		int					m_nPosterLine;

		CmdInfo()
			: m_szPosterFile(0)
			, m_nPosterLine(0)
		{
			m_Argument.clear();
		}

		template <typename T>
		void PushArg(const T& arg)
		{
			m_Argument.push_back(any(arg));
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
		void AddListener(unsigned int dwCommand, const F& f)
		{
			std::vector<functype>& vecListeners = m_mapListeners[dwCommand];
			functype fun = f;
			vecListeners.push_back(fun);
		}

		template <typename T1,typename T2,typename T3,typename T4,typename T5>
		void Notify(unsigned int unCommand, const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5)
		{
			m_unCommand = unCommand;
			BuildCmdArg(t1, t2, t3, t4, t5);
			Notify__();
		}

		template <typename T1,typename T2,typename T3,typename T4,typename T5>
		void Notify_dbg(unsigned int unCommand, const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
			const char* szFile, int nLine)
		{
			m_unCommand = unCommand;
			m_CurrentInfo.m_szPosterFile = szFile;
			m_CurrentInfo.m_nPosterLine = nLine;
			BuildCmdArg(t1, t2, t3, t4, t5);
			Notify__();
		}

		unsigned int GetCurrentCommand() const
		{
			return m_unCommand;
		}

		const CmdInfo& GetCurrentInfo() const
		{
			return m_CurrentInfo;
		}

	private:
		
		CmdMgr()
			: m_unCommand(0)
		{
			m_CurrentInfo.m_Argument.clear();
		}

		virtual ~CmdMgr()
		{
			m_CurrentInfo.m_Argument.clear();
		}

		template <typename T1,typename T2,typename T3,typename T4,typename T5>
		void BuildCmdArg(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
		{
			m_CurrentInfo.m_Argument.clear();

			if (!NC::is_same<T1, NC::_Nil>::value)
			{
				m_CurrentInfo.PushArg(t1);
			}
			if (!NC::is_same<T2, NC::_Nil>::value)
			{
				m_CurrentInfo.PushArg(t2);
			}
			if (!NC::is_same<T3, NC::_Nil>::value)
			{
				m_CurrentInfo.PushArg(t3);
			}
			if (!NC::is_same<T4, NC::_Nil>::value)
			{
				m_CurrentInfo.PushArg(t4);
			}
			if (!NC::is_same<T5, NC::_Nil>::value)
			{
				m_CurrentInfo.PushArg(t5);
			}
		}

		void Notify__()
		{
			std::map<unsigned int, std::vector<functype> >::iterator finditr = m_mapListeners.find(m_unCommand);
			if (finditr == m_mapListeners.end())
			{
				std::cout << "消息编号:" << m_unCommand << std::endl;
				std::cout << "没有找到关于该消息的任何回调函数" << std::endl;
				return;
			}

			std::vector<functype>::iterator itr = finditr->second.begin();
			std::vector<functype>::iterator enditr = finditr->second.end();
			for (; itr != enditr; ++itr)
			{
				(*itr)();
			}
		}
	protected:
		unsigned int m_unCommand;
		CmdInfo	m_CurrentInfo;

		std::map<unsigned int, std::vector<functype> > m_mapListeners;
	};
};

#define g_objEventMgr							(NC::CmdMgr::GetInstance())

#ifdef _DEBUG
#define NotifyMsg0(dwCommand) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj, \
	__FILE__, __LINE__))
#define NotifyMsg1(dwCommand,n1) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	(n1),NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj, \
	__FILE__, __LINE__))
#define NotifyMsg2(dwCommand,n1,n2) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	(n1),(n2),NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj, \
	__FILE__, __LINE__))
#define NotifyMsg3(dwCommand,n1,n2,n3) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	(n1),(n2),(n3),NC::_Nil_obj,NC::_Nil_obj, \
	__FILE__, __LINE__))
#define NotifyMsg4(dwCommand,n1,n2,n3,n4) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	(n1),(n2),(n3),(n4),NC::_Nil_obj, \
	__FILE__, __LINE__))
#define NotifyMsg5(dwCommand,n1,n2,n3,n4,n5) \
	(g_objEventMgr.Notify_dbg((dwCommand), \
	(n1),(n2),(n3),(n4),(n5), \
	__FILE__, __LINE__))
#else
#define NotifyMsg0(dwCommand) \
	(g_objEventMgr.Notify((dwCommand), \
	NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj))
#define NotifyMsg1(dwCommand,n1) \
	(g_objEventMgr.Notify((dwCommand), \
	(n1),NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj))
#define NotifyMsg2(dwCommand,n1,n2) \
	(g_objEventMgr.Notify((dwCommand), \
	(n1),(n2),NC::_Nil_obj,NC::_Nil_obj,NC::_Nil_obj))
#define NotifyMsg3(dwCommand,n1,n2,n3) \
	(g_objEventMgr.Notify((dwCommand), \
	(n1),(n2),(n3),NC::_Nil_obj,NC::_Nil_obj))
#define NotifyMsg4(dwCommand,n1,n2,n3,n4) \
	(g_objEventMgr.Notify((dwCommand),(n1),(n2),(n3),(n4),NC::_Nil_obj)
#define NotifyMsg5(dwCommand,n1,n2,n3,n4,n5) \
	(g_objEventMgr.Notify((dwCommand),(n1),(n2),(n3),(n4),(n5))
#endif

namespace NC
{
	template <typename T>
	T GetCurrentArg(unsigned int Pos)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		const NC::CmdInfo& info = g_objEventMgr.GetCurrentInfo();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (info.m_Argument.size() < Pos) {
			std::cout << "--- 消息绑定函数的参数过多或者Notify中传入参数数目不够 ---" << std::endl;
			std::cout << "消息编号：" << g_objEventMgr.GetCurrentCommand() << std::endl;
			std::cout << "位置：" << info.m_szPosterFile << info.m_nPosterLine << std::endl;
			throw;
		}

		--Pos;

#ifdef _DEBUG
		try {
			return NC::any_cast<T>(info.m_Argument.at(Pos));
		} catch (NC::bad_any_cast&) {
			std::cout << "--- GetCurrentArg 参数类型不匹配 ---" << std::endl;
			std::cout << "消息编号：" << g_objEventMgr.GetCurrentCommand() << std::endl;
			std::cout << "位置：" << info.m_szPosterFile << info.m_nPosterLine << std::endl;
			std::cout << "在Notify中传入参数位置" << Pos
				<< "参数类型" << info.m_Argument.at(Pos).type().name() << std::endl;
			std::cout << "实际需求的参数类型为" << typeid(T).name();
			throw;
		}
#else
		return NC::any_cast<T>(info.m_Argument.at(Pos));
#endif
	}

	template <typename T>
	T& GetCurrentArgRef(unsigned int Pos)
	{
		NC::reference_wrapper<T> r = GetCurrentArg<NC::reference_wrapper<T> >(Pos);
		return r;
	}

	template <typename T>
	const T& GetCurrentArgCRef(unsigned int Pos)
	{
		NC::reference_wrapper<const T> r = GetCurrentArg<NC::reference_wrapper<const T> >(Pos);
		return r;
	}
}

#include "NotifyCenterFunctional.h"

#endif //__NOTIFYCENTER_H__
