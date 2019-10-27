#pragma once
#include <mutex>
namespace EZVisual{

    class shared_mutex{
    public:
        void lock(){
            main_mtx.lock();
        }

        void lock_shared(){
            shared_mtx.lock();
            if((++shared_cnt) == 1)
                main_mtx.lock();
            shared_mtx.unlock();
        }

        void unlock(){
            main_mtx.unlock();
        }

        void unlock_shared(){
            shared_mtx.lock();
            if(--shared_cnt == 0)
                main_mtx.unlock();
            shared_mtx.unlock();
        }

        bool try_lock(){
            return main_mtx.try_lock();
        }

        bool try_lock_shared(){
            shared_mtx.lock();
            if(shared_cnt == 0){
                if(!main_mtx.try_lock()){
                    shared_mtx.unlock();
                    return false;
                }
                else ++shared_cnt;
            }
            shared_mtx.unlock();
        }
    private:
        unsigned int shared_cnt = 0;
        std::mutex main_mtx, shared_mtx;
    };

}
