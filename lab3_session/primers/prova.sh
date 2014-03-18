rm *.out
./primers > opt.out
./primerORG > org.out
diff opt.out org.out
