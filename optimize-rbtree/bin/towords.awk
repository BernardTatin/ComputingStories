#!/bin/awk -f

(/[A-Za-z]+/) {
    print tolower($1)
}
