# OS-Report
Q1(i). There are 3 student processes and 1 teacher process. Students are supposed to do their
assignments and they need 3 things pen, paper and question paper. The teacher has an
infinite supply of all the three things. One student has a pen, another has paper and another has
question paper. The teacher places two things on a shared table and the student having the
third complementary thing makes the assignment and tells the teacher on completion. The
teacher then places another two things out of the three and again the student having the third
thing makes the assignment and tells the teacher on completion. This cycle continues. WAP
to synchronize the teacher and the students.
Q1(ii). Two types of people can enter a library- students and teachers. After entering the
library, the visitor searches for the required books and gets them. In order to get
them issued, he goes to the single CPU there to process the issuing of
books. Two types of queues are there at the counter-one for students and one for
teachers. A student goes and stands at the tail of the queue for students and
similarly, the teacher goes and stands at the tail of the queue for teachers (FIFO). If
a student is being serviced and a teacher arrives at the counter, he would be the next
person to get service (PRIORITY-non preemptive). If two teachers arrive simultaneously they will stand in their queue to get service (FIFO). WAP to ensure that
the system works in a non-chaotic manner.
• If a teacher is being served and during the period when he is being served, another
teacher comes, then that teacher would get the service next. This process might
continue leading to an increase in the waiting time of students. Ensure in your program
that the waiting time of students is minimized.
