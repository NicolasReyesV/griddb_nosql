//
// MessagePack for C++ static resolution routine
//
// Copyright (C) 2008-2015 FURUHASHI Sadayuki
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
#ifndef MSGPACK_TYPE_SET_HPP
#define MSGPACK_TYPE_SET_HPP

#include "msgpack/versioning.hpp"
#include "msgpack/adaptor/adaptor_base.hpp"
#include "msgpack/adaptor/check_container_size.hpp"

#include <set>

namespace msgpack {

/// @cond
MSGPACK_API_VERSION_NAMESPACE(v1) {
/// @endcond

namespace adaptor {

template <typename T>
struct convert<std::set<T> > {
    msgpack::object const& operator()(msgpack::object const& o, std::set<T>& v) const {
        if(o.type != msgpack::type::ARRAY) { throw msgpack::type_error(); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        std::set<T> tmp;
        while(p > pbegin) {
            --p;
            tmp.insert(p->as<T>());
        }
        tmp.swap(v);
        return o;
    }
};

template <typename T>
struct pack<std::set<T> > {
    template <typename Stream>
    msgpack::packer<Stream>& operator()(msgpack::packer<Stream>& o, const std::set<T>& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for(typename std::set<T>::const_iterator it(v.begin()), it_end(v.end());
            it != it_end; ++it) {
            o.pack(*it);
        }
        return o;
    }
};

template <typename T>
struct object_with_zone<std::set<T> > {
    void operator()(msgpack::object::with_zone& o, const std::set<T>& v) const {
        o.type = msgpack::type::ARRAY;
        if(v.empty()) {
            o.via.array.ptr = nullptr;
            o.via.array.size = 0;
        } else {
            uint32_t size = checked_get_container_size(v.size());
            msgpack::object* p = static_cast<msgpack::object*>(o.zone.allocate_align(sizeof(msgpack::object)*size));
            msgpack::object* const pend = p + size;
            o.via.array.ptr = p;
            o.via.array.size = size;
            typename std::set<T>::const_iterator it(v.begin());
            do {
                *p = msgpack::object(*it, o.zone);
                ++p;
                ++it;
            } while(p < pend);
        }
    }
};

template <typename T>
struct convert<std::multiset<T> > {
    msgpack::object const& operator()(msgpack::object const& o, std::multiset<T>& v) const {
        if(o.type != msgpack::type::ARRAY) { throw msgpack::type_error(); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        std::multiset<T> tmp;
        while(p > pbegin) {
            --p;
            tmp.insert(p->as<T>());
        }
        tmp.swap(v);
        return o;
    }
};

template <typename T>
struct pack<std::multiset<T> > {
    template <typename Stream>
    msgpack::packer<Stream>& operator()(msgpack::packer<Stream>& o, const std::multiset<T>& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for(typename std::multiset<T>::const_iterator it(v.begin()), it_end(v.end());
            it != it_end; ++it) {
            o.pack(*it);
        }
        return o;
    }
};

template <typename T>
struct object_with_zone<std::multiset<T> > {
    void operator()(msgpack::object::with_zone& o, const std::multiset<T>& v) const {
        o.type = msgpack::type::ARRAY;
        if(v.empty()) {
            o.via.array.ptr = nullptr;
            o.via.array.size = 0;
        } else {
            uint32_t size = checked_get_container_size(v.size());
            msgpack::object* p = static_cast<msgpack::object*>(o.zone.allocate_align(sizeof(msgpack::object)*size));
            msgpack::object* const pend = p + size;
            o.via.array.ptr = p;
            o.via.array.size = size;
            typename std::multiset<T>::const_iterator it(v.begin());
            do {
                *p = msgpack::object(*it, o.zone);
                ++p;
                ++it;
            } while(p < pend);
        }
    }
};

} // namespace adaptor

/// @cond
}  // MSGPACK_API_VERSION_NAMESPACE(v1)
/// @endcond

}  // namespace msgpack

#endif // MSGPACK_TYPE_SET_HPP
