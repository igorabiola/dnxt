
tone = { A0=220  , Bb0=233 , B0=247 , C0=262  , Db0=277 , D0=294  , 
         Eb0=311 , E0=330  , F0=349 , Gb0=370 , G0=392  , Ab0=415 ,

         A1=440  , Bb1=466 , B1=493 , C1=523  , Db1=554 , D1=587  , 
         Eb1=622 , E1=659  , F1=698 , Gb1=740 , G1=784  , Ab1=831 ,

         A2=880  , Bb2=932 , B2=988 , C2=1046 , Db2=1109, D2=1175 , 
         Eb2=1244, E2=1318 , F2=1397, Gb2=1480, G2=1568 , Ab2=1661  }

function playmusic (music)
  for _,value in ipairs(music) do
    nxt:PlayTone( value.tone, value.duration )  
    lnxt.sleep( value.duration )
  end
end


doremifa = {{ tone = tone["C1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["E1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["C1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["C1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["C1"] , duration=500 },
            { tone = tone["G1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["E1"] , duration=500 },
            { tone = tone["E1"] , duration=500 },
            { tone = tone["E1"] , duration=500 },
            { tone = tone["C1"] , duration=500 },
            { tone = tone["D1"] , duration=500 },
            { tone = tone["E1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["F1"] , duration=500 },
            { tone = tone["F1"] , duration=500 }}


lnxt.sleep(1000)

playmusic(doremifa)          
