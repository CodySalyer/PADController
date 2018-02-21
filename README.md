# README #

This is a read me to help you get up and running with adding code

### What is this repository for? ###

This will contain all software for PADs project

### How do I get set up? ###

To get up and running
first download visual studios community https://www.visualstudio.com/vs/community/
Make sure you signed up for bitbucket from the add i sent you
second download our git client https://www.sourcetreeapp.com/
download the arduino client https://www.arduino.cc/en/Main/Software
download visual micro https://marketplace.visualstudio.com/items?itemName=VisualMicro.ArduinoIDEforVisualStudio 

Setup source tree with your bitbucket account to be connected.
	- During setup i chose to use the same name for the folder as the repo "Pads-Project"
	- when prompted to ignore files, choose to exclude common files EX: .exe, .obj, etc ...
	- After setup you should have the client pop up this will be where we'll save files


The Repo will be first seperated by language then by resources.
There will be an application already pre-loaded in both. 

### Contribution guidelines ###
Using git
First terms:
Pull: retrieve files from online server
Stage: prep and review files you're considering commiting
Commit: lock in the changes you've made and save a version to git
Push: send you updated commit to the server for others to have access to.
Branch: think tree, it holds a particular instance of the software version
Master: this is a particular branch that represents the fully functional software
fork: this is what is done what a feature is added, this way as you commit changes it doesn't affect others working on other branches or pulling from master.
Merge: after testing for bugs a particular branch can be merged back together, typically branches merge to master

Steps:
Pull the repo.
Determine task or function to add
Branch the code
Develop tool / function
test tool / function
merge tool with master
deal with conflicts 
repeat.

After you work on a file in the repo "Pads-project"
Open source tree you'll see "staged files", "unstaged files" 
When you've finished working save, stage and commit changes.

Some general guidelines about creating code
The goal is to keep this as an object oriented application.
All objects should be free from board specifics IE pin numbers, these should be assigned in the .ino application
C#: Create class definitions in an individual header file with a usefull namespace
C++: also use header files for class definitions

### Who do I talk to? ###

I'm assuming you can guess who you'll talk to if you have questions about using this.

If you have any questions please let me know if you're worried about breaking something i'd prefer if you ask sooner vs later.