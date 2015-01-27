#ifndef __POSTCMDEXFUNCTIONAL_H__
#define __POSTCMDEXFUNCTIONAL_H__

namespace postcmdex
{
	// =============================================================================================================
	//    template struct arg<T>
	//    template struct argref<T>
	//    template struct argcref<T>
	// =============================================================================================================
	template <typename T>
	struct arg
	{
		operator T() const
		{
			return GetCurrentArg<T>();
		}
	};

	template <typename T>
	struct argref
	{
		operator T&() const
		{
			return GetCurrentArgRef<T>();
		}
	};

	template <typename T>
	struct argcref
	{
		operator const T&() const
		{
			return GetCurrentArgCRef<T>();
		}
	};

	// =============================================================================================================
	//    struct cmd
	// =============================================================================================================
	struct cmd
	{
		operator DWORD() const
		{
			return g_objCmdState.GetCurrentCommand();
		}
	};

	// =============================================================================================================
	//    template struct null
	// =============================================================================================================
	template <typename T>
	struct null
	{
		operator T() const {
			return 0;
		}
	};

	// =============================================================================================================
	//    template class binder
	//    分为binder1, binder2, ..., binder9
	//    在对全局函数、类的static成员函数使用bind时会用到。
	//    不必直接使用。
	// =============================================================================================================
	template <typename F, typename T1>
	struct binder1
	{
		binder1(const F& f, const T1& t1)
			: m_f(f), m_t1(t1)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1);
		}

	private:
		const F m_f;
		const T1 m_t1;
	};

	template <typename F, typename T1, typename T2>
	struct binder2
	{
		binder2(const F& f, const T1& t1, const T2& t2)
			: m_f(f), m_t1(t1), m_t2(t2)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
	};

	template <typename F, typename T1, typename T2, typename T3>
	struct binder3
	{
		binder3(const F& f, const T1& t1, const T2& t2, const T3& t3)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4>
	struct binder4
	{
		binder4(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5>
	struct binder5
	{
		binder5(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
				const T5& t5)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
			, m_t5(t5)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4, m_t5);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
		const T5 m_t5;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6>
	struct binder6
	{
		binder6(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
				const T5& t5, const T6& t6)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
			, m_t5(t5), m_t6(t6)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4, m_t5, m_t6);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
		const T5 m_t5;
		const T6 m_t6;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7>
	struct binder7
	{
		binder7(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
				const T5& t5, const T6& t6, const T7& t7)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
			, m_t5(t5), m_t6(t6), m_t7(t7)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4, m_t5, m_t6, m_t7);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
		const T5 m_t5;
		const T6 m_t6;
		const T7 m_t7;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8>
	struct binder8
	{
		binder8(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
				const T5& t5, const T6& t6, const T7& t7, const T8& t8)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
			, m_t5(t5), m_t6(t6), m_t7(t7), m_t8(t8)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4, m_t5, m_t6, m_t7, m_t8);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
		const T5 m_t5;
		const T6 m_t6;
		const T7 m_t7;
		const T8 m_t8;
	};

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8, typename T9>
	struct binder9
	{
		binder9(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
				const T5& t5, const T6& t6, const T7& t7, const T8& t8, const T9& t9)
			: m_f(f), m_t1(t1), m_t2(t2), m_t3(t3), m_t4(t4)
			, m_t5(t5), m_t6(t6), m_t7(t7), m_t8(t8), m_t9(t9)
		{
		}

		void operator()(void) const
		{
			m_f(m_t1, m_t2, m_t3, m_t4, m_t5, m_t6, m_t7, m_t8, m_t9);
		}

	private:
		const F m_f;
		const T1 m_t1;
		const T2 m_t2;
		const T3 m_t3;
		const T4 m_t4;
		const T5 m_t5;
		const T6 m_t6;
		const T7 m_t7;
		const T8 m_t8;
		const T9 m_t9;
	};

	// =============================================================================================================
	//    template class mem_fn_wrapper
	//    分为mem_fn_wrapper0, mem_fn_wrapper1, ..., mem_fn_wrapper9
	//    在对类的non-static成员函数使用bind时会用到。
	//    不必直接使用。
	// =============================================================================================================
	template <typename C, typename R>
	struct mem_fn_wrapper0
	{
		mem_fn_wrapper0(R(C::*f)(void))
			: m_f(f)
		{
		}

		void operator()(C* ptr) const
		{
			(ptr->*m_f)();
		}

	private:
		R(C::*m_f)(void);
	};

	template <typename C, typename R,
			  typename T1>
	struct mem_fn_wrapper1
	{
		mem_fn_wrapper1(R(C::*f)(T1))
			: m_f(f)
		{
		}

		template <typename RT1>
		void operator()(C* ptr, const RT1& rt1) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1)
				);
		}

	private:
		R(C::*m_f)(T1);
	};

	template <typename C, typename R,
			  typename T1, typename T2>
	struct mem_fn_wrapper2
	{
		mem_fn_wrapper2(R(C::*f)(T1, T2))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2)
				);
		}

	private:
		R(C::*m_f)(T1, T2);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3>
	struct mem_fn_wrapper3
	{
		mem_fn_wrapper3(R(C::*f)(T1, T2, T3))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4>
	struct mem_fn_wrapper4
	{
		mem_fn_wrapper4(R(C::*f)(T1, T2, T3, T4))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5>
	struct mem_fn_wrapper5
	{
		mem_fn_wrapper5(R(C::*f)(T1, T2, T3, T4, T5))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6>
	struct mem_fn_wrapper6
	{
		mem_fn_wrapper6(R(C::*f)(T1, T2, T3, T4, T5, T6))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7>
	struct mem_fn_wrapper7
	{
		mem_fn_wrapper7(R(C::*f)(T1, T2, T3, T4, T5, T6, T7))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6, typename RT7>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6, const RT7& rt7) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6),
				static_cast<T7>(rt7)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6, T7);
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8>
	struct mem_fn_wrapper8
	{
		mem_fn_wrapper8(R(C::*f)(T1, T2, T3, T4, T5, T6, T7, T8))
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6, typename RT7, typename RT8>
		void operator()(C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6, const RT7& rt7, const RT8& rt8) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6),
				static_cast<T7>(rt7),
				static_cast<T8>(rt8)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6, T7, T8);
	};

	// =============================================================================================================
	//    template class const_mem_fn_wrapper
	//    分为const_mem_fn_wrapper0, const_mem_fn_wrapper1, ..., const_mem_fn_wrapper9
	//    在对类的non-static const成员函数使用bind时会用到。
	//    不必直接使用。
	// =============================================================================================================
	template <typename C, typename R>
	struct const_mem_fn_wrapper0
	{
		const_mem_fn_wrapper0(R(C::*f)(void)const)
			: m_f(f)
		{
		}

		void operator()(const C* ptr) const
		{
			(ptr->*m_f)();
		}

	private:
		R(C::*m_f)(void)const;
	};

	template <typename C, typename R,
			  typename T1>
	struct const_mem_fn_wrapper1
	{
		const_mem_fn_wrapper1(R(C::*f)(T1)const)
			: m_f(f)
		{
		}

		template <typename RT1>
		void operator()(const C* ptr, const RT1& rt1) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1)
				);
		}

	private:
		R(C::*m_f)(T1)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2>
	struct const_mem_fn_wrapper2
	{
		const_mem_fn_wrapper2(R(C::*f)(T1, T2)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2)
				);
		}

	private:
		R(C::*m_f)(T1, T2)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3>
	struct const_mem_fn_wrapper3
	{
		const_mem_fn_wrapper3(R(C::*f)(T1, T2, T3)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4>
	struct const_mem_fn_wrapper4
	{
		const_mem_fn_wrapper4(R(C::*f)(T1, T2, T3, T4)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5>
	struct const_mem_fn_wrapper5
	{
		const_mem_fn_wrapper5(R(C::*f)(T1, T2, T3, T4, T5)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6>
	struct const_mem_fn_wrapper6
	{
		const_mem_fn_wrapper6(R(C::*f)(T1, T2, T3, T4, T5, T6)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7>
	struct const_mem_fn_wrapper7
	{
		const_mem_fn_wrapper7(R(C::*f)(T1, T2, T3, T4, T5, T6, T7)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6, typename RT7>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6, const RT7& rt7) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6),
				static_cast<T7>(rt7)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6, T7)const;
	};

	template <typename C, typename R,
			  typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8>
	struct const_mem_fn_wrapper8
	{
		const_mem_fn_wrapper8(R(C::*f)(T1, T2, T3, T4, T5, T6, T7, T8)const)
			: m_f(f)
		{
		}

		template <typename RT1, typename RT2, typename RT3, typename RT4,
				  typename RT5, typename RT6, typename RT7, typename RT8>
		void operator()(const C* ptr, const RT1& rt1, const RT2& rt2, const RT3& rt3, const RT4& rt4,
						const RT5& rt5, const RT6& rt6, const RT7& rt7, const RT8& rt8) const
		{
			(ptr->*m_f)(
				static_cast<T1>(rt1),
				static_cast<T2>(rt2),
				static_cast<T3>(rt3),
				static_cast<T4>(rt4),
				static_cast<T5>(rt5),
				static_cast<T6>(rt6),
				static_cast<T7>(rt7),
				static_cast<T8>(rt8)
				);
		}

	private:
		R(C::*m_f)(T1, T2, T3, T4, T5, T6, T7, T8)const;
	};

	// =============================================================================================================
	//    template function bind
	//    与boost::bind类似，但不支持_1, _2等占位符。
	//    共有28个重载版本，分别用于支持：
	//    (1) 0~9个参数的普通函数（或类似物。）
	//    (2) 0~8个参数的类成员函数（non-const）
	//    (3) 0~8个参数的类成员函数（const）
	// =============================================================================================================
	template <typename F>
	const F bind(const F& f)
	{
		return f;
	}

	template <typename F, typename T1>
	binder1<F, T1> bind(const F& f, const T1& t1)
	{
		return binder1<F, T1>(f, t1);
	}

	template <typename F, typename T1, typename T2>
	binder2<F, T1, T2> bind(const F& f, const T1& t1, const T2& t2)
	{
		return binder2<F, T1, T2>(f, t1, t2);
	}

	template <typename F, typename T1, typename T2, typename T3>
	binder3<F, T1, T2, T3> bind(const F& f, const T1& t1, const T2& t2, const T3& t3)
	{
		return binder3<F, T1, T2, T3>(f, t1, t2, t3);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4>
	binder4<F, T1, T2, T3, T4> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return binder4<F, T1, T2, T3, T4>(f, t1, t2, t3, t4);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5>
	binder5<F, T1, T2, T3, T4, T5> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
										const T5& t5)
	{
		return binder5<F, T1, T2, T3, T4, T5>(f, t1, t2, t3, t4, t5);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6>
	binder6<F, T1, T2, T3, T4, T5, T6> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
											const T5& t5, const T6& t6)
	{
		return binder6<F, T1, T2, T3, T4, T5, T6>(f, t1, t2, t3, t4, t5, t6);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7>
	binder7<F, T1, T2, T3, T4, T5, T6, T7> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
												const T5& t5, const T6& t6, const T7& t7)
	{
		return binder7<F, T1, T2, T3, T4, T5, T6, T7>(f, t1, t2, t3, t4, t5, t6, t7);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8>
	binder8<F, T1, T2, T3, T4, T5, T6, T7, T8> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
													const T5& t5, const T6& t6, const T7& t7, const T8& t8)
	{
		return binder8<F, T1, T2, T3, T4, T5, T6, T7, T8>(f, t1, t2, t3, t4, t5, t6, t7, t8);
	}

	template <typename F, typename T1, typename T2, typename T3, typename T4,
			  typename T5, typename T6, typename T7, typename T8, typename T9>
	binder9<F, T1, T2, T3, T4, T5, T6, T7, T8, T9> bind(const F& f, const T1& t1, const T2& t2, const T3& t3, const T4& t4,
														const T5& t5, const T6& t6, const T7& t7, const T8& t8, const T9& t9)
	{
		return binder9<F, T1, T2, T3, T4, T5, T6, T7, T8, T9>(f, t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	template <typename C, typename R>
	binder1<mem_fn_wrapper0<C, R>, C*>
	bind(R(C::*pfn)(void), C* pobj)
	{
		return binder1<mem_fn_wrapper0<C, R>, C*>(pfn, pobj);
	}

	template <typename C, typename R,
			  typename T1, typename RT1>
	binder2<mem_fn_wrapper1<C, R, RT1>, C*, T1>
	bind(R(C::*pfn)(RT1), C* pobj,
		 const T1& t1)
	{
		return binder2<mem_fn_wrapper1<C, R, RT1>, C*, T1>(pfn, pobj, t1);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2>
	binder3<mem_fn_wrapper2<C, R, RT1, RT2>, C*, T1, T2>
	bind(R(C::*pfn)(RT1, RT2), C* pobj,
		 const T1& t1, const T2& t2)
	{
		return binder3<mem_fn_wrapper2<C, R, RT1, RT2>, C*, T1, T2>(
			pfn, pobj, t1, t2);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3>
	binder4<mem_fn_wrapper3<C, R, RT1, RT2, RT3>, C*, T1, T2, T3>
	bind(R(C::*pfn)(RT1, RT2, RT3), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3)
	{
		return binder4<mem_fn_wrapper3<C, R, RT1, RT2, RT3>, C*, T1, T2, T3>(
			pfn, pobj, t1, t2, t3);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4>
	binder5<mem_fn_wrapper4<C, R, RT1, RT2, RT3, RT4>, C*, T1, T2, T3, T4>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return binder5<mem_fn_wrapper4<C, R, RT1, RT2, RT3, RT4>, C*, T1, T2, T3, T4>(
			pfn, pobj, t1, t2, t3, t4);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5>
	binder6<mem_fn_wrapper5<C, R, RT1, RT2, RT3, RT4, RT5>, C*, T1, T2, T3, T4, T5>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5)
	{
		return binder6<mem_fn_wrapper5<C, R, RT1, RT2, RT3, RT4, RT5>, C*, T1, T2, T3, T4, T5>(
			pfn, pobj, t1, t2, t3, t4, t5);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6>
	binder7<mem_fn_wrapper6<C, R, RT1, RT2, RT3, RT4, RT5, RT6>, C*, T1, T2, T3, T4, T5, T6>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6)
	{
		return binder7<mem_fn_wrapper6<C, R, RT1, RT2, RT3, RT4, RT5, RT6>, C*, T1, T2, T3, T4, T5, T6>(
			pfn, pobj, t1, t2, t3, t4, t5, t6);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6,
			  typename T7, typename RT7>
	binder8<mem_fn_wrapper7<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7>, C*, T1, T2, T3, T4, T5, T6, T7>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6, RT7), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6, const T7& t7)
	{
		return binder8<mem_fn_wrapper7<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7>, C*, T1, T2, T3, T4, T5, T6, T7>(
			pfn, pobj, t1, t2, t3, t4, t5, t6, t7);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6,
			  typename T7, typename RT7, typename T8, typename RT8>
	binder9<mem_fn_wrapper8<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8>, C*, T1, T2, T3, T4, T5, T6, T7, T8>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8), C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6, const T7& t7, const T8& t8)
	{
		return binder9<mem_fn_wrapper8<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8>, C*, T1, T2, T3, T4, T5, T6, T7, T8>(
			pfn, pobj, t1, t2, t3, t4, t5, t6, t7, t8);
	}

	template <typename C, typename R>
	binder1<const_mem_fn_wrapper0<C, R>, const C*>
	bind(R(C::*pfn)(void)const, const C* pobj)
	{
		return binder1<const_mem_fn_wrapper0<C, R>, const C*>(pfn, pobj);
	}

	template <typename C, typename R,
			  typename T1, typename RT1>
	binder2<const_mem_fn_wrapper1<C, R, RT1>, const C*, T1>
	bind(R(C::*pfn)(RT1)const, const C* pobj,
		 const T1& t1)
	{
		return binder2<const_mem_fn_wrapper1<C, R, RT1>, const C*, T1>(pfn, pobj, t1);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2>
	binder3<const_mem_fn_wrapper2<C, R, RT1, RT2>, const C*, T1, T2>
	bind(R(C::*pfn)(RT1, RT2)const, const C* pobj,
		 const T1& t1, const T2& t2)
	{
		return binder3<const_mem_fn_wrapper2<C, R, RT1, RT2>, const C*, T1, T2>(
			pfn, pobj, t1, t2);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3>
	binder4<const_mem_fn_wrapper3<C, R, RT1, RT2, RT3>, const C*, T1, T2, T3>
	bind(R(C::*pfn)(RT1, RT2, RT3)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3)
	{
		return binder4<const_mem_fn_wrapper3<C, R, RT1, RT2, RT3>, const C*, T1, T2, T3>(
			pfn, pobj, t1, t2, t3);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4>
	binder5<const_mem_fn_wrapper4<C, R, RT1, RT2, RT3, RT4>, const C*, T1, T2, T3, T4>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return binder5<const_mem_fn_wrapper4<C, R, RT1, RT2, RT3, RT4>, const C*, T1, T2, T3, T4>(
			pfn, pobj, t1, t2, t3, t4);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5>
	binder6<const_mem_fn_wrapper5<C, R, RT1, RT2, RT3, RT4, RT5>, const C*, T1, T2, T3, T4, T5>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5)
	{
		return binder6<const_mem_fn_wrapper5<C, R, RT1, RT2, RT3, RT4, RT5>, const C*, T1, T2, T3, T4, T5>(
			pfn, pobj, t1, t2, t3, t4, t5);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6>
	binder7<const_mem_fn_wrapper6<C, R, RT1, RT2, RT3, RT4, RT5, RT6>, const C*, T1, T2, T3, T4, T5, T6>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6)
	{
		return binder7<const_mem_fn_wrapper6<C, R, RT1, RT2, RT3, RT4, RT5, RT6>, const C*, T1, T2, T3, T4, T5, T6>(
			pfn, pobj, t1, t2, t3, t4, t5, t6);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6,
			  typename T7, typename RT7>
	binder8<const_mem_fn_wrapper7<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7>, const C*, T1, T2, T3, T4, T5, T6, T7>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6, RT7)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6, const T7& t7)
	{
		return binder8<const_mem_fn_wrapper7<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7>, const C*, T1, T2, T3, T4, T5, T6, T7>(
			pfn, pobj, t1, t2, t3, t4, t5, t6, t7);
	}

	template <typename C, typename R,
			  typename T1, typename RT1, typename T2, typename RT2,
			  typename T3, typename RT3, typename T4, typename RT4,
			  typename T5, typename RT5, typename T6, typename RT6,
			  typename T7, typename RT7, typename T8, typename RT8>
	binder9<const_mem_fn_wrapper8<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8>, const C*, T1, T2, T3, T4, T5, T6, T7, T8>
	bind(R(C::*pfn)(RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8)const, const C* pobj,
		 const T1& t1, const T2& t2, const T3& t3, const T4& t4,
		 const T5& t5, const T6& t6, const T7& t7, const T8& t8)
	{
		return binder9<const_mem_fn_wrapper8<C, R, RT1, RT2, RT3, RT4, RT5, RT6, RT7, RT8>, const C*, T1, T2, T3, T4, T5, T6, T7, T8>(
			pfn, pobj, t1, t2, t3, t4, t5, t6, t7, t8);
	}

} // end of namespace postcmdex

#endif
