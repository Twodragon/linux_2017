#/bin/sh


POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -n|—-catalaguename)
    CATALAGUENAME="$2"
    shift # past argument
    shift # past value
    ;;
    -e|--extension)
    EXTENSION="$2"
    shift # past argument
    shift # past value
    ;;
    -a|--archivename)
    ARCHIVENAME="$2"
    shift # past argument
    shift # past value
    ;;
esac
done

mkdir $CATALAGUENAME
for EX in $EXTENSION;
do

	find ~/ -name "*.$EX" -type f -exec cp --backup=t {} ./$CATALAGUENAME/ \; 2>&1 | grep -v "Permission denied"

done

tar -czf $ARCHIVENAME.tar.gz $CATALAGUENAME
rm -r $CATALAGUENAME
echo done
