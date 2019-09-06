BEGIN	{
    lineasCodigo=0;
    comentarioLargo=0;
    contarElSiguiente=0;
}
comentarioLargo==1{
    for (i = 1; i<=NF ; i++ ) {
        if($i == "*/"){
            comentarioLargo=0;
            contarElSiguiente=1;
            break;
        }
    }
}
comentarioLargo==0{
    if(contarElSiguiente == 0){
        if($1 == "//" || $1 == "/*"){
        if($1 == "/*"){
            for (i=2; i<=NF; i++ ) {
                if($i == "*/"){
                    break;
                }
            }
            if(i > NF){
                comentarioLargo=1;
            }
        }
    }
    else{
        lineasCodigo++;
        i=2;
        for (i = 2; i<=NF ;i++ ) {
            if ($i == "//" || $i == "/*") {
                if ($i == "/*") {
                    for (j=i; j<=NF; j++ ) {
                        if($j == "*/"){
                            break;
                        }
                    }
                    if(j > NF){
                        comentarioLargo=1;
                        break;
                    }
                }
            }
        }
    }
    }
    else{
        contarElSiguiente=0;
    }
}
END	{
    print lineasCodigo;
}