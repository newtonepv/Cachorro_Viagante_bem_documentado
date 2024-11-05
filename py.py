import matplotlib.pyplot as plt
from collections import defaultdict

# 1. Seus dados
data = """
4,0.000041
4,0.000046
4,0.000047
4,0.000047
4,0.000046
4,0.000057
4,0.000043
4,0.000047
4,0.000048
4,0.000059
4,0.000057
4,0.000031
4,0.000028
4,0.000040
4,0.000048
4,0.000042
4,0.000050
4,0.000033
4,0.000046
4,0.000071
4,0.000051
4,0.000051
4,0.000036
4,0.000059
4,0.000046
4,0.000043
4,0.000047
4,0.000049
4,0.000049
4,0.000056
4,0.000039
4,0.000054
4,0.000045
4,0.000039
4,0.000047
4,0.000148
4,0.000153
4,0.000131
4,0.000120
4,0.000168
4,0.000224
4,0.000145
4,0.000168
4,0.000173
4,0.000170
4,0.000207
4,0.000062
4,0.000049
4,0.000046
4,0.000048
4,0.000048
4,0.000046
4,0.000044
4,0.000034
4,0.000059
4,0.000041
4,0.000034
4,0.000040
4,0.000046
4,0.000042
4,0.000044
4,0.000046
4,0.000043
4,0.000048
4,0.000045
4,0.000043
4,0.000038
4,0.000040
4,0.000051
4,0.000029
4,0.000041
4,0.000052
4,0.000056
4,0.000039
4,0.000046
4,0.000044
4,0.000056
4,0.000051
4,0.000043
4,0.000051
4,0.000048
4,0.000067
4,0.000197
4,0.000158
4,0.000131
4,0.000136
4,0.000146
4,0.000121
4,0.000201
4,0.000161
4,0.000180
4,0.000113
4,0.000155
4,0.000134
4,0.000160
4,0.000194
4,0.000048
4,0.000045
4,0.000047
4,0.000039
5,0.000067
5,0.000084
5,0.000070
5,0.000087
5,0.000088
5,0.000085
5,0.000088
5,0.000107
5,0.000118
5,0.000068
5,0.000077
5,0.000085
5,0.000081
5,0.000082
5,0.000075
5,0.000082
5,0.000073
5,0.000067
5,0.000076
5,0.000076
5,0.000072
5,0.000081
5,0.000049
5,0.000080
5,0.000070
5,0.000080
5,0.000073
5,0.000069
5,0.000068
5,0.000255
5,0.000240
5,0.000271
5,0.000251
5,0.000239
5,0.000226
5,0.000243
5,0.000236
5,0.000230
5,0.000273
5,0.000248
5,0.000295
5,0.000251
5,0.000234
5,0.000243
5,0.000228
5,0.000274
5,0.000070
5,0.000081
5,0.000070
5,0.000077
5,0.000052
5,0.000084
5,0.000074
5,0.000083
5,0.000084
5,0.000111
5,0.000077
5,0.000087
5,0.000072
5,0.000082
5,0.000077
5,0.000071
5,0.000078
5,0.000078
5,0.000085
5,0.000083
5,0.000079
5,0.000092
5,0.000083
5,0.000078
5,0.000067
5,0.000094
5,0.000074
5,0.000081
5,0.000079
5,0.000088
5,0.000089
5,0.000072
5,0.000080
5,0.000079
5,0.000079
5,0.000082
5,0.000063
5,0.000062
5,0.000080
5,0.000076
5,0.000090
5,0.000073
5,0.000068
5,0.000085
5,0.000069
5,0.000306
5,0.000232
5,0.000262
5,0.000260
5,0.000260
5,0.000284
5,0.000220
5,0.000297
5,0.000231
6,0.000536
6,0.000519
6,0.000492
6,0.000477
6,0.000163
6,0.000162
6,0.000172
6,0.000155
6,0.000163
6,0.000163
6,0.000178
6,0.000168
6,0.000154
6,0.000167
6,0.000143
6,0.000164
6,0.000161
6,0.000158
6,0.000142
6,0.000211
6,0.000139
6,0.000140
6,0.000158
6,0.000154
6,0.000145
6,0.000162
6,0.000190
6,0.000141
6,0.000166
6,0.000136
6,0.000154
6,0.000177
6,0.000147
6,0.000178
6,0.000177
6,0.000177
6,0.000532
6,0.000526
6,0.000525
6,0.000562
6,0.000676
6,0.000493
6,0.000523
6,0.000511
6,0.000464
6,0.000487
6,0.000562
6,0.000562
6,0.000512
6,0.000523
6,0.000538
6,0.000435
6,0.000149
6,0.000179
6,0.000156
6,0.000147
6,0.000151
6,0.000163
6,0.000139
6,0.000146
6,0.000140
6,0.000160
6,0.000103
6,0.000145
6,0.000144
6,0.000161
6,0.000154
6,0.000150
6,0.000177
6,0.000117
6,0.000136
6,0.000099
6,0.000135
6,0.000155
6,0.000143
6,0.000148
6,0.000154
6,0.000157
6,0.000156
6,0.000166
6,0.000164
6,0.000143
6,0.000138
6,0.000154
6,0.000144
6,0.000160
6,0.000156
6,0.000144
6,0.000151
6,0.000151
6,0.000163
6,0.000516
6,0.000502
6,0.000489
6,0.000558
6,0.000464
6,0.000554
6,0.000520
6,0.000533
6,0.000446
7,0.001058
7,0.001201
7,0.001178
7,0.001367
7,0.001149
7,0.000554
7,0.000376
7,0.000336
7,0.000385
7,0.000398
7,0.000342
7,0.000346
7,0.000357
7,0.000255
7,0.000369
7,0.000397
7,0.000395
7,0.000338
7,0.000366
7,0.000368
7,0.000337
7,0.000388
7,0.000323
7,0.000373
7,0.000376
7,0.000387
7,0.000254
7,0.000345
7,0.000340
7,0.000390
7,0.000403
7,0.000323
7,0.000371
7,0.000346
7,0.000334
7,0.000358
7,0.000252
7,0.000365
7,0.000390
7,0.000362
7,0.000496
7,0.001322
7,0.001283
7,0.001124
7,0.001265
7,0.001156
7,0.001129
7,0.001153
7,0.001273
7,0.001210
7,0.001190
7,0.001160
7,0.000394
7,0.000376
7,0.000368
7,0.000376
7,0.000329
7,0.000351
7,0.000399
7,0.000357
7,0.000343
7,0.000359
7,0.000340
7,0.000309
7,0.000399
7,0.000392
7,0.000410
7,0.000379
7,0.000467
7,0.000370
7,0.000395
7,0.000408
7,0.000344
7,0.000420
7,0.000414
7,0.000358
7,0.000344
7,0.000387
7,0.000321
7,0.000369
7,0.000367
7,0.000338
7,0.000343
7,0.000347
7,0.000341
7,0.001244
7,0.001153
7,0.001115
7,0.001230
7,0.001163
7,0.001211
7,0.001206
7,0.001201
7,0.001155
7,0.001228
7,0.001425
7,0.001135
7,0.001238
7,0.000344
7,0.000346
8,0.000870
8,0.000861
8,0.000907
8,0.000801
8,0.001006
8,0.000907
8,0.000978
8,0.000878
8,0.000916
8,0.000876
8,0.001092
8,0.000924
8,0.000914
8,0.000855
8,0.000904
8,0.001065
8,0.000930
8,0.000915
8,0.000930
8,0.000885
8,0.000920
8,0.000991
8,0.000929
8,0.000858
8,0.003328
8,0.003208
8,0.002922
8,0.003074
8,0.003106
8,0.003152
8,0.003586
8,0.003115
8,0.000924
8,0.000908
8,0.000931
8,0.000955
8,0.000995
8,0.001039
8,0.000928
8,0.000944
8,0.000896
8,0.000908
8,0.001000
8,0.000877
8,0.000991
8,0.000979
8,0.001019
8,0.000908
8,0.000974
8,0.000899
8,0.000896
8,0.001003
8,0.000904
8,0.000902
8,0.000937
8,0.000944
8,0.001187
8,0.003558
8,0.003449
8,0.003319
8,0.003367
8,0.003292
8,0.003307
8,0.003655
8,0.003405
8,0.003627
8,0.003267
8,0.002974
8,0.000723
8,0.000936
8,0.000678
8,0.001092
8,0.000924
8,0.001003
8,0.000991
8,0.000870
8,0.000964
8,0.000959
8,0.000882
8,0.000964
8,0.001047
8,0.001005
8,0.000930
8,0.000936
8,0.000977
8,0.000912
8,0.000912
8,0.000974
8,0.001035
8,0.000924
8,0.003199
8,0.003131
8,0.003057
8,0.003074
8,0.003338
8,0.003156
8,0.003253
8,0.003133
8,0.003210
8,0.000950
9,0.002262
9,0.002055
9,0.002143
9,0.002025
9,0.002093
9,0.002469
9,0.001770
9,0.002469
9,0.001907
9,0.002086
9,0.001955
9,0.002390
9,0.001971
9,0.001820
9,0.001960
9,0.001405
9,0.001501
9,0.001730
9,0.001845
9,0.001892
9,0.001881
9,0.005886
9,0.006339
9,0.006310
9,0.006530
9,0.006361
9,0.005984
9,0.006640
9,0.006511
9,0.004872
9,0.001556
9,0.001712
9,0.001702
9,0.001585
9,0.001806
9,0.001690
9,0.001875
9,0.002078
9,0.002119
9,0.001991
9,0.002099
9,0.002011
9,0.002313
9,0.001748
9,0.001849
9,0.001984
9,0.001334
9,0.001478
9,0.001896
9,0.001782
9,0.001932
9,0.001774
9,0.006487
9,0.006236
9,0.006296
9,0.006397
9,0.006331
9,0.006324
9,0.006558
9,0.001756
9,0.001871
9,0.001888
9,0.001707
9,0.001738
9,0.001870
9,0.001678
9,0.001413
9,0.001783
9,0.001541
9,0.001756
9,0.001486
9,0.001896
9,0.001887
9,0.001777
9,0.002091
9,0.001762
9,0.001906
9,0.001804
9,0.001916
9,0.001717
9,0.001651
9,0.005108
9,0.005833
9,0.006995
9,0.006527
9,0.006061
9,0.006251
9,0.006500
9,0.005954
9,0.006266
9,0.001873
9,0.001788
9,0.001880
9,0.001913
9,0.001942
9,0.001872
9,0.001876
9,0.001894
9,0.001918
9,0.001887
10,0.004869
10,0.004953
10,0.004934
10,0.004818
10,0.011219
10,0.016307
10,0.015785
10,0.015957
10,0.005141
10,0.005182
10,0.004866
10,0.004966
10,0.005038
10,0.004925
10,0.004769
10,0.004670
10,0.004925
10,0.014593
10,0.015585
10,0.015353
10,0.015971
10,0.015383
10,0.008400
10,0.004867
10,0.004685
10,0.004072
10,0.004837
10,0.004714
10,0.004930
10,0.004764
10,0.005268
10,0.005171
10,0.004764
10,0.016965
10,0.015699
10,0.015563
10,0.013285
10,0.004613
10,0.004674
10,0.004650
10,0.004693
10,0.004701
10,0.004545
10,0.004710
10,0.004831
10,0.004694
10,0.004814
10,0.016131
10,0.015455
10,0.016752
10,0.015301
10,0.012451
10,0.004802
10,0.004521
10,0.003610
10,0.004298
10,0.004628
10,0.004561
10,0.004641
10,0.004168
10,0.003650
10,0.004935
10,0.004530
10,0.004696
10,0.014512
10,0.015619
10,0.016129
10,0.016488
10,0.015752
10,0.004718
10,0.004611
10,0.004096
10,0.004823
10,0.003922
10,0.004184
10,0.004616
10,0.004879
10,0.004463
10,0.004854
10,0.005027
10,0.004706
10,0.014680
10,0.015432
10,0.015911
10,0.015986
10,0.015401
10,0.004095
10,0.004874
10,0.004759
10,0.004699
10,0.004620
10,0.004980
10,0.004888
10,0.004621
10,0.004909
10,0.004731
10,0.004980
10,0.004589
10,0.004252
10,0.004893
11,0.041668
11,0.041128
11,0.027352
11,0.012482
11,0.012343
11,0.012303
11,0.012297
11,0.012498
11,0.038252
11,0.041202
11,0.029846
11,0.012592
11,0.011169
11,0.011993
11,0.011570
11,0.012695
11,0.020958
11,0.041719
11,0.029530
11,0.011659
11,0.011504
11,0.012461
11,0.011556
11,0.011536
11,0.010667
11,0.025335
11,0.039914
11,0.038787
11,0.017351
11,0.012426
11,0.012346
11,0.012279
11,0.011165
11,0.012839
11,0.041490
11,0.042252
11,0.023753
11,0.012405
11,0.014315
11,0.014140
11,0.013451
11,0.014796
11,0.014170
11,0.013793
11,0.011649
11,0.012770
11,0.040570
11,0.041716
11,0.024658
11,0.012409
11,0.012364
11,0.012224
11,0.011810
11,0.011518
11,0.027918
11,0.037191
11,0.037159
11,0.012357
11,0.012094
11,0.010965
11,0.011988
11,0.013189
11,0.020788
11,0.043861
11,0.024703
11,0.012430
11,0.013015
11,0.012657
11,0.012698
11,0.025073
11,0.042781
11,0.013654
11,0.012932
11,0.012263
11,0.013214
11,0.012730
11,0.032140
11,0.042151
11,0.027926
11,0.012367
11,0.013654
11,0.012563
11,0.012504
11,0.012338
11,0.037488
11,0.041367
11,0.025281
11,0.012293
11,0.012441
11,0.012456
11,0.012523
11,0.012686
11,0.042282
11,0.040152
11,0.012831
11,0.010324
11,0.012853
11,0.012396
11,0.011616
11,0.012394
12,0.061789
12,0.072242
12,0.024130
12,0.024320
12,0.025073
12,0.082527
12,0.037368
12,0.025953
12,0.024845
12,0.051802
12,0.083069
12,0.025947
12,0.023363
12,0.027616
12,0.090746
12,0.038328
12,0.026417
12,0.027042
12,0.063375
12,0.074607
12,0.025455
12,0.026246
12,0.023291
12,0.083551
12,0.036977
12,0.025661
12,0.026496
12,0.048936
12,0.083310
12,0.024418
12,0.024917
12,0.022838
12,0.062273
12,0.064261
12,0.024532
12,0.028116
12,0.024692
12,0.084456
12,0.044665
12,0.025313
12,0.025130
12,0.035945
12,0.087486
12,0.028410
12,0.026601
12,0.028203
12,0.069273
12,0.061469
12,0.026635
12,0.028027
12,0.042663
12,0.084317
12,0.027277
12,0.028152
12,0.028510
12,0.095156
12,0.027933
12,0.026542
12,0.028530
12,0.088589
12,0.028872
12,0.024993
12,0.078090
12,0.040286
12,0.024796
12,0.024832
12,0.059066
12,0.071210
12,0.025613
12,0.025711
12,0.049387
12,0.093427
12,0.028131
12,0.028046
12,0.028347
12,0.049051
12,0.079885
12,0.025757
12,0.025062
12,0.025309
12,0.074836
12,0.063227
12,0.027444
12,0.025880
12,0.026697
12,0.086901
12,0.040582
12,0.027505
12,0.026770
12,0.074240
12,0.035546
12,0.029698
12,0.043453
12,0.064028
12,0.033300
12,0.035006
12,0.035810
12,0.034975
12,0.027681
12,0.034114
4,0.000053
5,0.000096
10,0.006366
12,0.101147
"""

# 2. Processar os dados
# Usar um dicionário para agrupar os tempos por número
tempos_por_numero = defaultdict(list)

# 3. Ler os dados e agrupar os tempos
for line in data.splitlines():
    if line.strip():  # Ignorar linhas em branco
        numero, tempo = line.split(",")
        numero = int(numero)
        tempo = float(tempo)
        tempos_por_numero[numero].append(tempo)

# 4. Calcular a média dos tempos para cada número
medias = {numero: sum(tempos) / len(tempos) for numero, tempos in tempos_por_numero.items()}

# 5. Preparar dados para plotagem
numeros = list(medias.keys())
medias_de_tempos = list(medias.values())

print(medias_de_tempos)

# 6. Plotar os resultados
plt.figure(figsize=(8, 5))
plt.plot(numeros, medias_de_tempos, marker='o', linestyle='-', color='b')

plt.title('Média dos Tempos por Número')
plt.xlabel('Número')
plt.ylabel('Média dos Tempos (s)')
plt.grid(True)
plt.show()