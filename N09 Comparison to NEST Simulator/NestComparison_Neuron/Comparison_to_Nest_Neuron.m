time = out.Voltages.time
Ie_376 = out.Voltages.signals(1).values
Ie_350 = out.Voltages.signals(2).values
Ie_400 = out.Voltages.signals(3).values

T = table(time, Ie_376, Ie_350, Ie_400)
writetable(T, 'VoltagesSimulink.xls')