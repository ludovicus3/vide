/* This file is part of the VIDE Project
*
*  The VIDE Project is free software: you can redistribute it and/or
*  modify it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  The VIDE Project is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*  Authors: Jason Galens <bogey.jlg@gmail.com>
*/
#include <clotho/thread.h>

#include <errno.h>

static pthread_key_t key;
static pthread_once_t key_once = PTHREAD_ONCE_INIT;

static void
create_key() {
  pthread_key_create(&key, NULL);
}

namespace vide {

namespace clotho {

thread_t::~thread_t() {
}

thread_t*
thread_t::current() {
  thread_t* thread;

  pthread_once(&key_once, create_key);

  if ((thread = reinterpret_cast<thread_t*>(pthread_getspecific(key))) == NULL) {
    thread = new thread_t(pthread_self());
    pthread_setspecific(key, thread);
  }

  return thread;
}


//  thread_t(thread_t&&) noexcept = default;
//  thread_t& operator = (thread_t&&) noexcept = default;

void
thread_t::start() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  // maybe do some scheduling setup here
  // if inherit
  // pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
  // else
  // int sched_policy;
  // pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
  //

  // STACK SIZE
  /*
  int result = pthread_attr_setstack_size(&attr, stacksize);
  */

  int result = pthread_create(&_id, &attr, thread_t::execute_thread, this);
  if (result == EPERM) {
    pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
    result = pthread_create(&_id, &attr, thread_t::execute_thread, this);
  }

  pthread_attr_destroy(&attr);

  if (result != 0) {
    _id = 0;
  }
}

void
thread_t::terminate() {
  int result = pthread_cancel(_id);
  if (result != 0) {
    // danger will robinson
  }
}

void
thread_t::wait() {
  pthread_join(_id, NULL);
}

/* protected: ---------------------------------------------------------------*/
void
thread_t::run() { 
}

/* private: -----------------------------------------------------------------*/
thread_t::thread_t(pthread_t id) : _id(id) {}

void*
thread_t::execute_thread(void* arg) {
  thread_t* thread = reinterpret_cast<thread_t*>(arg);

  pthread_once(&key_once, create_key);
  pthread_setspecific(key, thread);

  thread->run();
}

} // namespace clotho

} // namespace vide

