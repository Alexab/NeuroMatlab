#!/usr/bin/env python3

import nest
import pylab

#Neurons
n_params = [{"I_e": 376.0}, {"I_e": 350.0}, {"I_e": 400.0}]
neurons = nest.Create("iaf_psc_alpha", 3, n_params)


#Multimeter
m_params = {"withtime": True, "record_from": ["V_m"], "interval": 0.01}
multimeters = nest.Create("multimeter", 3, params = m_params)

#Connections
nest.Connect(multimeters, neurons, "one_to_one")

#Simulation
nest.Simulate(400.0)

#Graphics
dmm1 = nest.GetStatus(multimeters)[0]
dmm2 = nest.GetStatus(multimeters)[1]
dmm3 = nest.GetStatus(multimeters)[2]

pylab.figure(1)

Voltage1 = dmm1["events"]["V_m"]
ts1 = dmm1["events"]["times"]
pylab.plot(ts1, Voltage1, label = "I_e = 376,0 pA")

Voltage2 = dmm1["events"]["V_m"]
ts1 = dmm1["events"]["times"]
pylab.plot(ts1, Voltage2, label = "I_e = 350,0 pA")

Voltage3 = dmm1["events"]["V_m"]
ts1 = dmm1["events"]["times"]
pylab.plot(ts1, Voltage3, label = "I_e = 400,0 pA")

pylab.xlim(60, 80)
pylab.xlabel("time, ms")
pylab.ylabel("V_m, mV")
pylab.legend()

pylab.show()