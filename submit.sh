#!/bin/bash

#
# Script that removes unwanted elements for submission to the moulinette
#

function switch_to_submit_branch() {
	if [ $(git branch --list submit) ]; then
		git branch -D submit
	fi
	git checkout -b submit
}

function checkout_submodules_as_standalone() {
	# Recreates all submodules as standalone files
	SUBMODULES=$(git config --file .gitmodules --get-regexp path | awk '{ print $2 }')
	for SUBMODULE in $SUBMODULES; do
		# Get submodule info 
		SUBMODULE_COMMIT=$(git config --file .gitmodules --get "submodule.$SUBMODULE.commit")
		SUBMODULE_URL=$(git config --file .gitmodules --get "submodule.$SUBMODULE.url")
		# Deinit submodule
		git submodule deinit -f $SUBMODULE
		git rm --cached $SUBMODULE
		rm -rf $SUBMODULE
		# Clone back the submodule as a singular repository
		git clone $SUBMODULE_URL $SUBMODULE
		# Checkout the submodule at the specific commit
		cd $SUBMODULE
		git checkout $SUBMODULE_COMMIT
		cd ..
	done
}

function remove_git_files() {
	find . -wholename "./*/.git" -exec rm -rf {} \;
	find . -name ".gitignore" -type f -exec rm -rf {} \;
	find . -name ".gitmodules" -type f -exec rm -rf {} \;
	find . -name ".gitattributes" -type f -exec rm -rf {} \;
	find . -name ".git-blame-ignore-revs" -type f -exec rm -rf {} \;
}

function clean_unwanted_files() {
	# If a Makefile exists, run fclean
	if [ -f "Makefile" ]; then
		make fclean
	else
		TO_REMOVE=.o,.a,.out,.vscode,.dSYM,.d,.so,.swp,.nfs*
		for EXT in ${TO_REMOVE//,/ }
		do
			find . -name "*.$EXT" -type f -exec rm -rf {} \;
		done
	fi

	# Remove this script
	rm -rf submit.sh
}


function git_push() {
	# Move to submit branch
	git add .
	# if the qit command exists, use it
	if [ -x "$(command -v qit)" ]; then
		qit commit chore -a submit "branch setup"
	else
		git commit -sm "chore: submit branch setup"
	fi
	git push origin submit --force
}

switch_to_submit_branch
checkout_submodules_as_standalone

#tmp: Remove libft tests folder
rm -rf ./libft/tests

remove_git_files
clean_unwanted_files
git_push
