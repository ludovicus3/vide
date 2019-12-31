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
#ifndef VIDE__CLOTHO__THREAD_H
#define VIDE__CLOTHO__THREAD_H

#include <pthread.h>

namespace vide {

namespace clotho {

class thread_t {
public:
  thread_t() = default;
  virtual ~thread_t() = default;

  static thread_t* current();

  thread_t(thread_t&&) noexcept = default;
  thread_t& operator = (thread_t&&) noexcept = default;

  void start();
  void sleep(unsigned long nsec);
  void terminate();

protected:
  virtual void run(); // default is to do nothing

private:
  thread_t(pthread_t id);

  thread_t(const thread_t&) = delete;
  thread_t& operator = (const thread_t&) = delete;

  static void* pthread_runner(void* arg);

  pthread_t _id;
}; // class thread_t

} // namespace clotho

} // namespace vide

#endif // VIDE__CLOTHO__THREAD_H

