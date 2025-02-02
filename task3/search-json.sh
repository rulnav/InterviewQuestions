#!/bin/bash

rg -o '"model":"[^"]*"' bigf.json | sort | uniq -c | tee model_counts.txt 
# 33327094 "\"123456789\""
# 33328584 "\"broken\""
# 33338513 "\"DRV1\""
# 33333959 "\"DSD07461\""
# 33332531 "\"HGST2048T\""
# 33337292 "\"HGST3T\""
# 33337967 "\"HGST8T\""
#       1 "\"MODEL\""
# 33332954 "\"RDV2\""
# 33329611 "\"SCSI3HD\""
# 33327742 "\"SSDDC1\""
# 33328579 "\"SSDF1\""
# 33345174 "\"SSDLP2\""

