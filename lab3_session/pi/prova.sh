rm *.out
./pi > opt.out
./pi_org > org.out
diff opt.out org.out
