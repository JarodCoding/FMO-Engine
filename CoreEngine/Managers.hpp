#pragma once
#include "Pointers.hpp"
namespace CoreEngine::Execution::Memory::Manager {
	template<I> class Wrapper
	{
	public:
		inline template<T> auto allocate(size_t size) {
			return static_cast(I, this)->allocate<T>(size);
		}
		inline template<T> auto try_allocate(size_t amount) {
			return static_cast(I, this)->try_allocate<T>(size);
		}
		inline template<P> bool try_free(P ptr) {
			return static_cast(I, this)->try_free<P>(ptr);
		}
		inline template<P> void free() {
			return static_cast(I, this)->free<P>(ptr);
		}
		inline template<T> bool try_free(local_ptr<T,I> ptr) {
			return static_cast(T, this)->try_free<T>(ptr);
		}
		inline template<T> void free(local_ptr<T,I> ptr) {
			return static_cast(T, this)->free<T>(ptr);
		}
	protected:
	private:
		
	};
}