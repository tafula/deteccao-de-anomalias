rm -f AnomalyDetection
rm -f learner
rm -f tester

rm -f test/img/f*/*
touch test/img/f0/empty
touch test/img/f1/empty

rm -f test/mask/f*/*
touch test/mask/f0/empty
touch test/mask/f1/empty

rm -f input/learn/img/*
touch input/learn/img/empty

rm -f input/learn/mask/*
touch input/learn/mask/empty

rm -f output/ad_masks/ped1/t001/*
touch output/ad_masks/ped1/t001/empty
