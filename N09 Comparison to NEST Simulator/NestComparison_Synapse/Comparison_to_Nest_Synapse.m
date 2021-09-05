time_s = out.SynCurrents.time
SynCurrent_pA = out.SynCurrents.signals(1).values


T = table(time_s, SynCurrent_pA)
writetable(T, 'SynCurrents.xls')