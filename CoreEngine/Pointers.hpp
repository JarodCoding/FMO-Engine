#pragma once
template<T, P> class ptr;
template<T, W> class local_ptr: ptr<T,local_ptr>;
#include "Managers.hpp"