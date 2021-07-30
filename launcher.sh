#!/bin/bash 
#simple launcher for execution multiple scripts

executor()
{
	./initializer				#execute main script  
	while true; do
    	read -p "> " input  		#processing user's input until 'exit' command won't be executed
    	case $input in
        	exit ) exit;;
		clear ) clear;;
		help ) 
		 printf "List of available commands during session:\n\tendsession -> closing session\n\thelp -c -> list of all commands\n\thelp -s -> list of all satellites\n\ttrack <satl_name> -> printing sattelite's current position on world map\nList of commands available beyond session:\n\topensession -> starting session\n\tclear -> cleaning screen\n\thelp -> list of all commands\n\texit -> closing programm\n"; ;;
		opensession) ./initializer;;
    		esac
	done
	complete "put" in
}
export -f executor			#now this function is available for terminal

gnome-terminal -- bash -c "executor; exec bash"	 #run everything above in new window
