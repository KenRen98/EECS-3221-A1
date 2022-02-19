
1.	A general outline of your understanding of the assigned work. 

For this Assignment, we are required to write a program which concurrently calculates the sum and the average of several datasets in multiple files. Each file contains a series of double floating numbers that separated by a white space. The program should dynamically create new child processes for sum calculation and element counting of each dataset, while the parent process should wait one of them finish or wait all of them finish and collect results from each child and print out the result and also the combined average. Both the pipe + fork version and the Pthread version will be evaluated.


2.	A clear statement about the assigned work/components you believe you have done/completed successfully. 

A.	Both functions would work perfectly in the case where Parent processes wait for each child to finish, as an extra, the pipe version also implemented the other case where Parent processes take and print the result of any finished child.

B.	Both programs dynamically assign child processes based on the input argument numbers.

C.	Pipe data transferring with a shared pipe. Retrieving all in one time or retrieving one by one are both implemented. (See comments in the file)


3.	A statement about the work you believe you might have not completed successfully (feel free to comment on related problems, if any). 

A.	Dynamic memory allocation on input argument name is not implemented, where you might face a file that has a name longer than the max I set. But it would add much more complexity for pipe writing and reading, specially reading.

B.	Dynamic waiting for any child to finish is not implemented in Pthread Version, since pthread_join() requires specific PID, the possible work around might be using sleep() and running thread watching method.

C.	The program did not consider when a wrong file name is given, it will make mistake if the given file name does not exist, this can be easily implemented by adding a if file_ptr==null then exit() condition, it would work on both version, just using different exit. And once an exit code is caught, the parent process can just deduct on the argc value so the next loop where result is being retrieved, the wrong one can be skipped.


4.	 Anything else related to your work that you might wish to comment upon. 
Please copy the above entries and paste into your report to use as a template when typing your report.

A.	The program might need more datasets and larger datasets for testing to prove reliability.
