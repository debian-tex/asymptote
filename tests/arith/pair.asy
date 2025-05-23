import TestLib;

StartTest("complex addition");
assert((1,0)+(0,1) == (1,1));
EndTest();
StartTest("complex subtraction");
assert((1,0)-(0,1) == (1,-1));
EndTest();
StartTest("complex multiplication");
assert((1,2)*(2,1) == (0,5));
EndTest();
StartTest("complex division");
assert((0,5)/(2,1) == (1,2));
EndTest();
StartTest("length(pair)");
assert(length((0.0,1.0)) == 1.0);
EndTest();
StartTest("conj()");
assert(conj((0.0,1.0)) == (0.0,-1.0));
EndTest();
