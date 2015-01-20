#pragma once

#include <map>
#include <functional>

namespace notifycenter
{
	const char*		s_szPosterFile;
	int				s_nPosterLine;
	unsigned int	s_unPosterCmd;

	// have a placeholder base-type:
	struct base {
		base(int n) : nPNum(n) {};
		virtual ~base() {};
		virtual const type_info& type() const { return typeid(void); }
		int nPNum;
	};

	// have a derived type to wrap the 
	//  actual functor object:
	struct wrapped0 : base {
		typedef std::function<void(void)> func0_type;
		func0_type f0;
		wrapped0(func0_type aFunc) : base(0), f0(aFunc) { };
		virtual const type_info& type() const { return typeid(f0); }
	};
	template <typename T1>
	struct wrapped1 : base {
		typedef std::function<void(T1)> func1_type;
		func1_type f1;
		wrapped1(func1_type aFunc) : base(1), f1(aFunc) { };
		virtual const type_info& type() const { return typeid(f1); }
	};
	template <typename T1,typename T2>
	struct wrapped2 : base {
		typedef std::function<void(T1,T2)> func2_type;
		func2_type f2;
		wrapped2(func2_type aFunc) : base(2), f2(aFunc) { };
		virtual const type_info& type() const { return typeid(f2); }
	};
	template <typename T1,typename T2,typename T3>
	struct wrapped3 : base {
		typedef std::function<void(T1,T2,T3)> func3_type;
		func3_type f3;
		wrapped3(func3_type aFunc) : base(3), f3(aFunc) { };
		virtual const type_info& type() const { return typeid(f3); }
	};
	template <typename T1,typename T2,typename T3,typename T4>
	struct wrapped4 : base {
		typedef std::function<void(T1,T2,T3,T4)> func4_type;
		func4_type f4;
		wrapped4(func4_type aFunc) : base(4), f4(aFunc) { };
		virtual const type_info& type() const { return typeid(f4); }
	};
	template <typename T1,typename T2,typename T3,typename T4,typename T5>
	struct wrapped5 : base {
		typedef std::function<void(T1,T2,T3,T4,T5)> func5_type;
		func5_type f5;
		wrapped5(func5_type aFunc) : base(5), f5(aFunc) { };
		virtual const type_info& type() const { return typeid(f5); }
	};

	class events {
	private:
		// Hold a base-type pointer:
		std::shared_ptr<base> p_base;
	public:
		//拷贝构造
		events(const events& a)	{
//			assert(a.p_base && p_base && a.p_base->nPNum == p_base->nPNum);
			p_base = a.p_base;
		}
		// Assign object with any function:
		events& operator=(const events& a) {
//			assert(a.p_base && p_base && a.p_base->nPNum == p_base->nPNum);
			p_base = a.p_base;
		};

		// Initialize object with any function:
		events(std::function<void (void)> aFunc)
			: p_base(new wrapped0(aFunc)) {
			std::cout << "wrapped0" << std::endl;
		};
		// Assign object with any function:
		events& operator=(std::function<void (void)> aFunc) {
			p_base = std::shared_ptr<base>(new wrapped0(aFunc));
			return *this;
		};
		// Call the function by casting the base
		//  pointer back to its derived type:
		void operator()() const {
			wrapped0* p_wrapped = dynamic_cast< wrapped0* >(p_base.get());
			if(p_wrapped) // <- if cast successful
				p_wrapped->f0();
			else
				throw std::runtime_error("Invalid arguments to function object call!");
		};

		template <typename T1>
		// Initialize object with any function:
		events(std::function<void (T1)> aFunc)
			: p_base(new wrapped1<T1>(aFunc)) {
			std::cout << "wrapped1" << std::endl;
		};
		// Assign object with any function:
		template <typename T1>
		events& operator=(std::function<void (T1)> aFunc) {
			p_base = std::shared_ptr<base>(new wrapped1<T1>(aFunc));
			return *this;
		};
		// Call the function by casting the base
		//  pointer back to its derived type:
		template <typename T1>
		void operator()(T1 t1) const {
			wrapped1<T1>* p_wrapped = dynamic_cast< wrapped1<T1>* >(p_base.get());
			if(p_wrapped) // <- if cast successful
				p_wrapped->f1(t1);
			else
			{
				std::cout << "--- 参数类型不匹配 ---\n"
					<< "消息编号:" << s_unPosterCmd << std::endl
					<< "位置:" << s_szPosterFile << "(" << s_nPosterLine << ")" << std::endl
					<< "原始类型为" << p_base.get()->type().name() << std::endl
					<< "传入参数类型为" << typeid(T1).name() << std::endl;
				throw std::runtime_error("Invalid arguments to function object call!");
			}
		};
	};

	/*
	class events {
	private:
	// Hold a base-type pointer:
	std::shared_ptr<base> p_base;
	public:
	// Initialize object with any function:
	template <typename... Args>
	events(std::function<void(Args...)> aFunc) :
	p_base(new wrapped<Args...>(aFunc)) { };
	// Assign object with any function:
	template <typename... Args>
	events& operator=(std::function<void(Args...)> aFunc) {
	p_base = std::shared_ptr<base>(new wrapped<Args...>(aFunc));
	return *this;
	};
	// Call the function by casting the base
	//  pointer back to its derived type:
	template <typename... Args>
	void operator()(Args... args) const {
	wrapped<Args...>* p_wrapped = dynamic_cast< wrapped<Args...>* >(p_base.get());
	if(p_wrapped) // <- if cast successful
	p_wrapped->f(args...);
	else
	throw std::runtime_error("Invalid arguments to function object call!");
	};
	};
	*/

	class CmdMgr
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
			std::vector<events>& vecListeners = m_mapListeners[dwCommand];
			events fun = f;
			vecListeners.push_back(fun);
		}

		void Notify(unsigned int unCMD)
		{
			auto finditr = m_mapListeners.find(unCMD);
			if (finditr == m_mapListeners.end())
			{
				return;
			}

			for (auto& invokObj : finditr->second)
			{
				(invokObj)();
			}
		}

		void Notify_dbg(unsigned int unCMD, const char* szFile, int nLine)
		{
			s_unPosterCmd = unCMD;
			s_szPosterFile = szFile;
			s_nPosterLine = nLine;
			Notify(unCMD);
		}

		template <typename T1>
		void Notify(unsigned int unCMD, T1 t1)
		{
			auto finditr = m_mapListeners.find(unCMD);
			if (finditr == m_mapListeners.end())
			{
				return;
			}

			for (auto& invokObj : finditr->second)
			{
				(invokObj)(t1);
			}
		}

		template <typename T1>
		void Notify_dbg(unsigned int unCMD, T1 t1, const char* szFile, int nLine)
		{
			s_unPosterCmd = unCMD;
			s_szPosterFile = szFile;
			s_nPosterLine = nLine;
			Notify(unCMD, t1);
		}

	protected:
		std::map<unsigned int, std::vector<events> > m_mapListeners;
	};
};

#define g_objCmdMgr									(notifycenter::CmdMgr::GetInstance())

#ifdef _DEBUG
#define NotifyMsg0(dwCommand)				 (g_objCmdMgr.Notify_dbg((dwCommand),__FILE__, __LINE__))
#define NotifyMsg1(dwCommand,n1)			 (g_objCmdMgr.Notify_dbg((dwCommand),(n1),__FILE__, __LINE__))
#define NotifyMsg2(dwCommand,n1,n2)			 (g_objCmdMgr.Notify_dbg((dwCommand),(n1),(n2),__FILE__, __LINE__))
#define NotifyMsg3(dwCommand,n1,n2,n3)		 (g_objCmdMgr.Notify_dbg((dwCommand),(n1),(n2),(n3),__FILE__, __LINE__))
#define NotifyMsg4(dwCommand,n1,n2,n3,n4)	 (g_objCmdMgr.Notify_dbg((dwCommand),(n1),(n2),(n3),(n4),__FILE__, __LINE__))
#define NotifyMsg5(dwCommand,n1,n2,n3,n4,n5) (g_objCmdMgr.Notify_dbg((dwCommand),(n1),(n2),(n3),(n4),(n5),__FILE__, __LINE__))
#else
#define NotifyMsg0(dwCommand)						(g_objCmdMgr.Notify((dwCommand)))
#define NotifyMsg1(dwCommand,n1)					(g_objCmdMgr.Notify((dwCommand),(n1)))
#define NotifyMsg2(dwCommand,n1,n2)					(g_objCmdMgr.Notify((dwCommand),(n1),(n2)))
#define NotifyMsg3(dwCommand,n1,n2,n3)				(g_objCmdMgr.Notify((dwCommand),(n1),(n2),(n3)))
#define NotifyMsg4(dwCommand,n1,n2,n3,n4)			(g_objCmdMgr.Notify((dwCommand),(n1),(n2),(n3),(n4)))
#define NotifyMsg5(dwCommand,n1,n2,n3,n4,n5)		(g_objCmdMgr.Notify((dwCommand),(n1),(n2),(n3),(n4),(n5)))
#endif

