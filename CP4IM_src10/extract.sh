CLOSED="class.closed"
for FILE in ./**/*noclass.csv;
do
  echo "Éxécution sur le fichier $FILE.";
  echo "Écriture dans le fichier "${FILE/"noclass.csv"/"$CLOSED"}".";
    #echo "-10";
  ./eclat -s10 -tc $FILE "${FILE/"noclass.csv"/"$CLOSED"}"
  #echo "Vérification du fichier $FILE.";
done

exit 0
