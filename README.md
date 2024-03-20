## Red-Black-tree ##
Task Management System using Red Black Trees in C++


<ins>**REQUIREMENTS**</ins>


<ins>Add Assignee</ins>
Users should be able to add new assignees to the system, providing
information such as First Name, Last Name, address, and DOB.

<ins>Search Assignee by ID</ins>
Search Function to find an assignee by their ID.

<ins>Search Assignee by name</ins> 
Search Function to find an assignee by their first and last name, if
there is more than 1 person with the same name; display all the Assignees with that name.
Search Assignee with no task Assigned Shift Tasks of one assignee to another Assignee

<ins>Delete Assignee</ins>
If an assignee has not yet completed their tasks, they cannot be deleted.
Add Task: Users should be able to add new tasks to the system, providing information such as
task description, priority level, and the assignee ID (team member).

<ins>Complete Task</ins>
Tasks should be marked as completed when they are finished. Users should
be able to update the task status accordingly.

<ins>Print Task Queue</ins>
The system should provide an option to display the list of tasks, sorted in
ascending order of priority.

<ins>Find Highest Priority Task</ins> Users should be able to find and display the task with the highest
priority (lowest priority value) without removing it from the queue.

<ins>Find Task by Assignee</ins>
The system should allow users to search for tasks assigned to a
specific team member and display them.

<ins>Count Total Tasks</ins> Users should be able to obtain a count of the total number of tasks in the
system.

<ins>Update Task Priority</ins> The system should allow users to update the priority level of a specific
task without removing it from the queue.

<ins>Clear Completed Tasks</ins> Users should be able to remove all completed tasks from the system,
keeping only pending tasks.

<ins>Display All Completed Tasks</ins> The system should provide a feature to display all completed
tasks, which can be helpful for generating progress reports.

<ins>Search for Task by Priority Range</ins>
Users should be able to search for tasks within a specified
priority range and display them.



**2. RED-BLACK Tree Implementation:**

The red-black tree should store task records. Each node in the red-black tree represents a task
in the system. The node structure of the task tree includes the following fields:

-> Task ID: A unique identifier for each task.
-> Description: A text description of the task.
-> Priority Level: An integer value representing the task's urgency, with lower values indicating
    higher priority.
    
->Assignee ID: Every Assignee should have a unique ID.

-> Another tree would be created to store the details of Assignee, which would include:
-> ----First Name
-> ----Last Name
-> ----Address
-> ----Date of birth: in the format of day/month/year
-> ----Assignee ID: This will be auto-generated.



**CODE IMPLEMENTATION**
Code has been done in c++ according to requirements. It is written in simpler ways with proper comments. If there is
any query related to code you can contact me at : awanhashim800@gmail.com

