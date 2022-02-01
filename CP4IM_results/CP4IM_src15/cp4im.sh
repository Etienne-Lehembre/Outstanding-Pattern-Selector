CLOSED="-class.closed"
for SEED_EXTENT in ./**/*.txt;
do
  echo "Éxécution sur les fichiers $SEED_EXTENT et "${SEED_EXTENT/".txt"/"$CLOSED"}".";
  ../CP4IM_Lattice/main $SEED_EXTENT "${SEED_EXTENT/".txt"/"$CLOSED"}" &
done


#for SEED_CLOSED in ./**/*"$CLOSED";
#do
#  echo "Suppression de $SEED_CLOSED.";
#  rm $SEED_CLOSED;
#done

exit 0
