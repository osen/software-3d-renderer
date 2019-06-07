#ifdef _WIN32
  #define THREADPOOL_DISABLE
#endif

#ifdef STD_SR1_DEBUG
  #define THREADPOOL_DISABLE
#endif

#define THREADPOOL_THREADS 4

#ifndef THREADPOOL_DISABLE
  #include <pthread.h>
  #include <semaphore.h>
#endif

#include <vector>

template <typename T>
class ThreadPool;

template <typename T>
class ThreadUnit
{
  friend class ThreadPool<T>;

private:
  T t;
#ifndef THREADPOOL_DISABLE
  pthread_t thread;
  sem_t start;
  sem_t stop;
#endif
  ThreadPool<T> *tp;

};

template <typename T>
class ThreadPool
{
public:
  ThreadPool() : func(NULL)
  {
#ifndef THREADPOOL_DISABLE
    units.resize(THREADPOOL_THREADS);
#else
    units.resize(1);
#endif

    for(typename std::vector<ThreadUnit<T> >::iterator it =
      units.begin(); it != units.end(); it++)
    {
      it->tp = this;

#ifndef THREADPOOL_DISABLE
      if(sem_init(&it->start, 0, 0) == -1)
      {
        throw std::exception();
      }

      if(sem_init(&it->stop, 0, 0) == -1)
      {
        throw std::exception();
      }

      if(pthread_create(&it->thread, NULL, entry,
        (void *)&(*it)) != 0)
      {
        it->thread = pthread_self();
        throw std::exception();
      }
#endif
    }
  }

  ~ThreadPool()
  {
    func = NULL;

#ifndef THREADPOOL_DISABLE
    for(typename std::vector<ThreadUnit<T> >::iterator it =
      units.begin(); it != units.end(); it++)
    {
      sem_post(&it->start);
      pthread_join(it->thread, NULL);
      sem_destroy(&it->start);
      sem_destroy(&it->stop);
    }
#endif
  }

  size_t size()
  {
    return units.size();
  }

  T& at(size_t idx)
  {
    return units.at(idx).t;
  }

  void execute(void (*func)(T& t))
  {
    this->func = func;

#ifndef THREADPOOL_DISABLE
    for(typename std::vector<ThreadUnit<T> >::iterator it =
      units.begin(); it != units.end(); it++)
    {
      sem_post(&it->start);
    }

    for(typename std::vector<ThreadUnit<T> >::iterator it =
      units.begin(); it != units.end(); it++)
    {
      sem_wait(&it->stop);
    }
#else
    func(units.at(0).t);
#endif

    this->func = NULL;
  }

private:
  std::vector<ThreadUnit<T> > units;
  void (*func)(T& t);

#ifndef THREADPOOL_DISABLE
  static void *entry(void *ptr)
  {
    ThreadUnit<T> *tu = (ThreadUnit<T> *)ptr;

    while(true)
    {
      sem_wait(&tu->start);

      if(!tu->tp->func)
      {
        break;
      }
      else
      {
        tu->tp->func(tu->t);
      }

      sem_post(&tu->stop);
    }

    return NULL;
  }
#endif

};

