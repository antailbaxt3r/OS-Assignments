# OS Online 3

## Work

All functions are declared in the ```cricket.c``` file and functions have been exposed using the header ```cricket.h``` file. At the same time, driver code is written in ```driver.c```<br/>

I have created a ```mem``` object (shared memory) of the ```struct memory``` which stores the complete match related information. <br/>

The ```mem``` object stores 2 ```struct Team``` objects for each team which in turn store team information as well as an array of 11 ```struct Players``` objects, which represent individual players. <br/>

At this moment, the code is broken and doesn't work and I was unable to debug it. I have created the umpire, team1 and team2 processes using ```fork()``` and worked on umpire and batsmen process, but I was unable to work on the bowlers process. This is part of the reason why the code is broken.

Of the things that work, the input is being taken by each process correctly using functions : 
<ul>
    <li><code>init_umpire()</code> </li>
    <li><code>init_team1()</code> </li>
    <li><code>init_team2()</code> </li>
</ul>
and teamOut1 and teamOut2 can be created using the <code>write_to_files()</code> function. <br/>

## Work Not Done

- Unable to finish the complete program
- Unable to work on bowler process
- Only able to work on batsman process of team1
- Code is broken because of improper signal usage
