

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;
sem_t paper, pen, question;

void *student(void *num) {

  int student_num = *(int *)num;

  if(student_num == 0) {
    sem_wait(&pen);
  }
  else if(student_num == 1) {  
    sem_wait(&paper);
  }
  else {
    sem_wait(&question);
  }

  // Student has all 3 items now
  printf("Student %d has finished assignment\n", student_num);

  // Signal teacher
  sem_post(&mutex);

  // Wait for teacher to signal
  sem_wait(&paper);
  sem_wait(&pen); 
  sem_wait(&question);

  // Release resources
  sem_post(&paper);
  sem_post(&pen);
  sem_post(&question);

  pthread_exit(NULL);
}

void *teacher() {

  while(1) {
    // Wait for student to finish  
    sem_wait(&mutex);

    // Give next 2 items 
    sem_post(&paper);
    sem_post(&pen);

    // Wait for student to finish 
    sem_wait(&mutex);

    // Give next 2 items
    sem_post(&question);
    sem_post(&paper);

    // Wait for student to finish
    sem_wait(&mutex);  

    // Give next 2 items
    sem_post(&pen);
    sem_post(&question);
  }
}

int main() {

  // Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&paper, 0, 0);
  sem_init(&pen, 0, 1);
  sem_init(&question, 0, 0);

  pthread_t tid1, tid2, tid3, teacher_tid;
  int student_nums[3] = {0, 1, 2};

  // Create student threads
  pthread_create(&tid1, NULL, student, &student_nums[0]);
  pthread_create(&tid2, NULL, student, &student_nums[1]);
  pthread_create(&tid3, NULL, student, &student_nums[2]);

  // Create teacher thread
  pthread_create(&teacher_tid, NULL, teacher, NULL);

  // Join student threads
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  // Destroy semaphores
  sem_destroy(&mutex);
  sem_destroy(&paper);
  sem_destroy(&pen);
  sem_destroy(&question);
  
  return 0;
}


