git checkout master
make
pdeSolver -nx 1000 -ny 1000 -i 100 -o saida_master.dat
git checkout $1
make
pdeSolver -nx 1000 -ny 1000 -i 100 -o saida_branch.dat
echo "master:"
cat saida_master.dat | head -n 15
echo "$1:"
cat saida_branch.dat | head -n 15
diff saida_master.dat saida_branch.dat
