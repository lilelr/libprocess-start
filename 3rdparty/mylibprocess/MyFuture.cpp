

#include <assert.h>

#include <atomic>
#include <list>
#include <memory> // TODO(benh): Replace shared_ptr with unique_ptr.
#include <set>
#include <type_traits>
#include <utility>
#include <vector>

#include <glog/logging.h>

#include <process/clock.hpp>
#include <process/owned.hpp>
#include <process/pid.hpp>
#include <process/timer.hpp>

#include <stout/abort.hpp>
#include <stout/check.hpp>
#include <stout/duration.hpp>
#include <stout/error.hpp>
#include <stout/lambda.hpp>
#include <stout/none.hpp>
#include <stout/option.hpp>
#include <stout/preprocessor.hpp>
#include <stout/result.hpp>
#include <stout/result_of.hpp>
#include <stout/synchronized.hpp>
#include <stout/traits.hpp>
#include <stout/try.hpp>

#include <stout/os/strerror.hpp>

#include "Mylatch.hpp"

namespace process{

    template <typename T>
    class MyFuture;

    template <typename T>
    class MyFuture{
    public:

        MyFuture();

        /*implicit*/ MyFuture(const T& t);

        /*implicit*/ MyFuture(const MyFuture<T>& that);


        typedef lambda::function<void()> DiscardCallback;
        typedef lambda::function<void(const T&)> ReadyCallback;
        typedef lambda::function<void(const std::string&)> FailedCallback;
        typedef lambda::function<void()> DiscardedCallback;

        bool isPending() const;
        bool isReady() const;
        bool isFailed() const;
        bool isDiscarded() const;

        // Waits for this future to become ready, discarded, or failed.
        bool await(const Duration& duration = Seconds(-1)) const;

//        typedef lambda::function<void(const MyFuture<T>&) AnyCallback;

      const T& get() const;
    protected:

    private:

        enum State{
        PENDING,
        READY,
        FAILED,
        DISCARDED,
    };

    struct Data{
        Data();
        ~Data() = default;

        std::atomic_flag lock = ATOMIC_FLAG_INIT;
        State state;
        bool discard;
        bool associated;

        void clearAllCallbacks();
        // One of:
        //   1. None, the state is PENDING or DISCARDED.
        //   2. Some, the state is READY.
        //   3. Error, the state is FAILED; 'error()' stores the message.
        Result<T> result;

        std::vector<DiscardCallback > onDiscardCallbacks;
        std::vector<ReadyCallback> onReadyCallbacks;
        std::vector<FailedCallback> onFailedCallbacks;
        std::vector<DiscardedCallback> onDiscardedCallbacks;
//        std::vector<AnyCallback> onAnyCallbacks;


    };

    std::shared_ptr<Data> data;

    bool set(const T& t);

//        bool set(const T&& t);


        template<typename U>
    bool _set( U&& u);

    };

    template <typename T>
    MyFuture<T>::MyFuture():data(new Data()){
      LOG(INFO)<<"construct function MyFuture<T>::MyFuture()";
    }

    template <typename T>
    MyFuture<T>::MyFuture(const T &t) :data(new Data()){
        LOG(INFO)<<"copy construct function  MyFuture<T>::MyFuture(const T &t)";
        set(t);

    }

    template <typename T>
    MyFuture<T>::MyFuture(const MyFuture<T> & that) :data(that.data){
        LOG(INFO)<<"copy construct function  MyFuture<T>::MyFuture(const MyFuture<T> &that )";

    }

    template <typename T>
    MyFuture<T>::Data::Data():state(PENDING),discard(false),associated(false), result(None()){
        LOG(INFO)<<"construct function MyFuture<T>::Data::Data()";

    }

    template <typename T>
    void MyFuture<T>::Data::clearAllCallbacks() {
        onDiscardCallbacks.clear();
        onDiscardedCallbacks.clear();
        onFailedCallbacks.clear();
        onReadyCallbacks.clear();
    }

    template <typename T>
    bool MyFuture<T>::isPending() const {
        return data->state == PENDING;
    }

    template <typename T>
    bool MyFuture<T>::isReady() const {
        return data->state == READY;
    }

    template <typename T>
    bool MyFuture<T>::isFailed() const {
        return data->state == FAILED;
    }

    template <typename T>
    bool MyFuture<T>::isDiscarded() const {
        return data->state == DISCARDED;
    }

    // Waits for this future to become ready, discarded, or failed.
    template <typename T>
    bool MyFuture<T>::await(const Duration &duration) const {
        Owned<Mylatch> latch(new Mylatch());

        bool pending = false;
        synchronized (data->lock){
            if(data->state == PENDING){
                pending = true;
            }
        }

        if(pending){
            return latch->await(duration);
        }
        return true;

    }

    template <typename T>
    const T& MyFuture<T>::get() const{
        return this->data->result.get();
    }

    template <typename T>
    bool MyFuture<T>::set(const T &t) {
        LOG(INFO)<<"MyFuture<T>::set(const T &t)";
        return _set(t);
    }

//    template <typename T>
//    bool MyFuture<T>::set(const T&& t) {
//        LOG(INFO)<<"MyFuture<T>::set(const T&& t)";
//
//        return _set(std::move(t));
//    }

    template <typename T>
    template <typename U>
    bool MyFuture<T>::_set( U &&u) {
        LOG(INFO)<<"MyFuture<T>::_set( U &&u) ";
        bool result = false;

        synchronized (data->lock){
            if(data->state == PENDING){
                data->result = std::forward<U>(u);
                data->state = READY;
                result = true;
            }
        }

        if(result){
            data->clearAllCallbacks();
        }

        return result;
    }

}

using namespace process;
int main(){
    MyFuture<int> m1 = 323;
    MyFuture<int> m2   = m1;

    LOG(INFO)<<m1.isReady();

    LOG(INFO)<<m1.get();
    LOG(INFO)<<m2.get();

    m1 = 4;
    LOG(INFO)<<m1.get();
    LOG(INFO)<<m2.get();



    return 0;
}