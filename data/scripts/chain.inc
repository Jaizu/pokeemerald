ChainNumber::
    addvar VAR_CHAIN, 1
    buffernumberstring 0, VAR_CHAIN
    msgbox TextoCool, 2
    end
   
TextoCool::
    .string "Cadena: {STR_VAR_1}, de {STR_VAR_2}.$"
   
AddChain::
    addvar VAR_CHAIN, 1
    end
