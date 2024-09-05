/*
1. Check Message Queues Using ipcs:
code int terminal -- ipcs -q

2. Interpreting the Output:
The ipcs -q command will display a table of all message queues, showing the following columns:

key: The key used to create the message queue.
msqid: The message queue identifier.
owner: The owner of the message queue.
perms: The permissions associated with the message queue.
used-bytes: The number of bytes currently in use in the queue.
messages: The number of messages currently in the queue.

3. Cleaning Up:
code in terminal -- ipcrm -q <msqid>

Summary:
In Part (a), message queues are created and immediately deleted, so they do not appear in the ipcs -q output.
In Part (b), message queues are created with IPC_PRIVATE, which ensures unique identifiers. These queues are not deleted by the program, so they will appear in the ipcs -q output with unique msqid values.

*/