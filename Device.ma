[top]
components : inflator@Inflator
components : Con_DS

in : in1
in : in2

out : out1
out : out2

Link : in1 in1@Con_DS
Link : in2 in2@Con_DS
Link : out1@Con_DS out1
Link : out2@Con_DS in@inflator
Link : out@inflator out2

[inflator]
inflateProcessingTime : 00:00:02:00

[Con_DS]
components : controller@controller
components : ds@DepthSensor

in : in1
in : in2

out : out1
out : out2

Link : in1 in1@controller
Link : in2 in2@ds
Link : out3@controller out1
Link : out2@controller out2
Link : out1@controller in1@ds
Link : out@ds in2@controller

[ds]
prepareProcessingTime : 00:00:00:010
sendProcessingTime : 00:00:00:010

[controller]
processProcessingTime : 00:00:00:010
cmpSetProcessingTime : 00:00:03:00