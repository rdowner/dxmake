Changelog
=========

## 2.13

Fix GCC warnings.

Re-license as BSD


## 2.12

Fix a bug for the following sequence:

    install: target1 target2

    target1: objectX
	...

    target2: objectX
	...

In this case target2 was not being executed if it did not exist.


## 2.11

Fix a nasty bug when reassigning a variable in the form: `X= $(X) a b c`


## 2.10

Conditionalize use of stat `st_gen`, linux doesn't implement the field.


## 2.9

Create a port for dmake, rename dmake to dxmake to avoid a port
conflict with someone else's dmake.

Add `.ifhost`, `.ifos`, and `.ifarch` conditionals

Remove old AMIGA ifdefs


## 2.8

Save and restore TOPDIR when running the .include directive in
order to support multiple .include directives.

Do not misinterpret .. and ./ as dot directives.

Add `.iffile` directive

When multiple dependancies for a target exist, and one is stale,
run ALL the related commands.  In the example below we would run
cmds A and cmds B if any dependancy is stale.

    $(OBJS) : $(OD)
        cmds A....

    $(OBJS) : $(SRCS)
        cmds B....

When we execute a dependancy set, if the target file exists we
check whether the timestamp has changed or not.  If it has not
changed we assume a passive update.. that is, a situation such
as with prototype generation where the rule executed but no
change was made.  When this case occurs we touch the target file
to update its timestamp and flag the dependancy as a passive update.
This may propogate and touch other targets (such as object files).


## 2.7

Fix the list ordering so commands for this situation:

    $(OBJS) : $(OD)
        cmds....

    $(OBJS) : $(SRCS)
        cmds....

Are executed in the proper order.


## 2.6

Added `.include <path>`

Added automatic `$(TOP)` calculation for `.include` sequences

Rewrote dependancy handler


## 2.2

Found bug in parse.c relating to symbol buffers, would screw up
symbolic replace in multiple-dependancy line.
