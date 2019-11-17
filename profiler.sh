#!/bin/bash
NSIZES=( 32 50 64 100 128 200 256 300 400 512 1000 1024 2000 2048 3000 4000 4096 5000 10000 )
ITERS=10 #objetivo: printar cada coisa ordenada pelo tamanho

#LINHAS: tempo médio, memory bandwith, data cache miss ratio, flops_dp, flops_avx
LW='likwid-perfctr -C 3 -g'
LWOUT='likwid_outputs'
if [ ! -d "$LWOUT" ]; then 
    mkdir $LWOUT
fi
if [ ! -d "$LWOUT/new" ]; then
    mkdir $LWOUT/new
fi
if [ ! -d "$LWOUT/old" ]; then
    mkdir $LWOUT/old
fi
if [ "$(ls -A $LWOUT/new)" ]; then
    mv $LWOUT/new/* $LWOUT/old
fi

if [ -e "table" ]; then
    rm table
fi
echo "# Nsize Avgtime Memband Missrate FDP AVX" > table

S='_'
SOLVER="-m ./pdeSolver -i $ITERS"

echo "" > lwresultstable
#variáveis de medição
AVGTIME='RDTSC Runtime'
MEMBAND='L3 bandwidth'
MISSRATIO='L2 miss ratio'
DPFLOPS='DP MFLOP'
AVXFLOPS='AVX DP MFLOP'


for N in "${NSIZES[@]}"
do
    echo "N is $N"

    G='L3'
    DATE=$(date +"%Y-%m-%d_%T")
    FILE_OUT=$(echo $N$S$DATE)
    OUT_NAME=$(echo $G$S$FILE_OUT)
    $LW $G $SOLVER -nx $N -ny $N -o $FILE_OUT.dat > $LWOUT/new/$OUT_NAME

    #tempo médio - talvez n tenha tamanho fixo
    AVGTIME_R=$(grep "$AVGTIME" $LWOUT/new/$OUT_NAME | cut -c 2- | rev | cut -c 2- | cut -f1 -d"|" | rev)

    #banda de memória
    MEMBAND_R=$(grep "$MEMBAND" $LWOUT/new/$OUT_NAME | cut -c 2- | rev | cut -c 2- | cut -f1 -d"|" | rev)

    G='L2CACHE'
    OUT_NAME=$(echo $G$S$FILE_OUT)
    $LW $G $SOLVER -nx $N -ny $N -o $FILE_OUT.dat > $LWOUT/new/$OUT_NAME
    ##miss ratio
    MISS_R=$(grep "$MISSRATIO" $LWOUT/new/$OUT_NAME | cut -c 2- | rev | cut -c 2- | cut -f1 -d"|" | rev)

    G='FLOPS_DP'
    OUT_NAME=$(echo $G$S$FILE_OUT)
    $LW $G $SOLVER -nx $N -ny $N -o $FILE_OUT.dat > $LWOUT/new/$OUT_NAME
    #dpmflops
    FDP_R=$(grep "$DPFLOPS" $LWOUT/new/$OUT_NAME | grep -v 'AVX' | cut -c 2- | rev | cut -c 2- | cut -f1 -d"|" | rev)

    #avxflops
    AVX_R=$(grep "$AVXFLOPS" $LWOUT/new/$OUT_NAME | cut -c 2- | rev | cut -c 2- | cut -f1 -d"|" | rev)


    echo $N $AVGTIME_R $MEMBAND_R $MISS_R $FDP_R $AVX_R >> table

done
