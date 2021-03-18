#!/bin/sh

# A basic and simple shell script for managine a CD collection.
#

# ------------------
# GLOBAL VARIBALES
# ------------------
# These variables are used throught the program.

menu_choice=""
current_cd=""
title_file="title.cdb"
tracks_file="tracks.cdb"
temp_file=/tmp/cdb.$$
trap 'rm -f $temp_file'  EXIT

# ---------------------
# UTILITIES FUNCTIONS
# ---------------------
get_return(){
    echo -e "Press return \c"
    read x
    return 0
}


get_confirm(){
    echo -e "Are you sure? [Y/n]: \c"
    while true
    do
        read x
        case "$x" in
            y | yes | Y | Yes | YES)
                return 0;;
            n | no | N | No | NO)
                echo
                echo "Cancelled"
                return 1;;
            *)
                echo "Please enter yes or no";;
        esac
    done
}

#
get_menu_choice(){}

#
insert_title(){}

#
insert_track(){}

#
add_record_tracks(){}

#
add_records(){}

#
find_cd(){}

#
update_cd(){}

#
count_cds(){}

#
remove_records(){}


#
list_tracks(){}


#
main(){}


#####
main
