

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_QUEUE_SIZE 10

sem_t student_mutex, teacher_mutex;
sem_t service_sem;

int student_queue[MAX_QUEUE_SIZE], student_count = 0;
int teacher_queue[MAX_QUEUE_SIZE], teacher_count = 0;

void *student() {
  sem_wait(&student_mutex);
  student_queue[student_count++] = pthread_self();
  printf("Student %lu queued\n", pthread_self());
  sem_post(&student_mutex);

  sem_wait(&service_sem);
  printf("Student %lu got service\n", pthread_self());
  sem_post(&service_sem);
}

void *teacher() {
  sem_wait(&teacher_mutex);
  teacher_queue[teacher_count++] = pthread_self();
  printf("Teacher %lu queued\n", pthread_self());
  sem_post(&teacher_mutex);
  
  if(student_count > 0) {
    sem_wait(&student_mutex);
  }
  
  sem_wait(&service_sem);
  printf("Teacher %lu got service\n", pthread_self());
  sem_post(&service_sem);
  
  if(student_count > 0) {
    sem_post(&student_mutex); 
  }
}

int main() {

  sem_init(&student_mutex, 0, 1);
  sem_init(&teacher_mutex, 0, 1);
  sem_init(&service_sem, 0, 1);

  pthread_t s1, s2, t1, t2;

  pthread_create(&s1, NULL, student, NULL);
  pthread_create(&t1, NULL, teacher, NULL);
  pthread_create(&s2, NULL, student, NULL);
  pthread_create(&t2, NULL, teacher, NULL);

  pthread_join(s1, NULL);
  pthread_join(t1, NULL);
  pthread_join(s2, NULL);
  pthread_join(t2, NULL);

  sem_destroy(&student_mutex);
  sem_destroy(&teacher_mutex);
  sem_destroy(&service_sem);

  return 0;
}
