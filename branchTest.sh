git checkout master
make clean
make
rm saida_master.dat
pdeSolver -nx 3000 -ny 3000 -i 10 -o saida_master.dat
git checkout $1
make clean
make
rm saida_branch.dat
pdeSolver -nx 3000 -ny 3000 -i 10 -o saida_branch.dat
echo "master:"
cat saida_master.dat | head -n 15
echo "$1:"
cat saida_branch.dat | head -n 15
diff saida_master.dat saida_branch.dat
