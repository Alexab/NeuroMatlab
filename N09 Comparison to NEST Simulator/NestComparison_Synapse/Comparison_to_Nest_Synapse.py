#!/usr/bin/env  python3

import nest
import pylab
import pandas as pd

nest.SetKernelStatus({'resolution': 1.0})

#GENERATOR
g_params = [{"start": 0.0, "stop": 500.0, "spike_times":[100.0, 300.0] }]
spikeGenerator = nest.Create("spike_generator", 1, g_params)
print(nest.GetStatus(spikeGenerator))
print()

#NEURON
n_params = [{"I_e": 0.0}]
neuron = nest.Create("iaf_psc_alpha", 1, n_params )
print(nest.GetStatus(neuron))
print()

#SPIKE DETECTOR
spikeDetector = nest.Create('spike_detector', n=1)

#MULTIMETER
m_params = {"withtime": True, "record_from": ["I_syn_ex"]}
multimeter = nest.Create("multimeter", 1, params = m_params)

#CONNECTIONS
syn_dict = {"model": "static_synapse", "weight": 1.0, "delay": 1.0}
nest.Connect(spikeGenerator, spikeDetector, 'one_to_one')
nest.Connect( spikeGenerator, neuron, "one_to_one", syn_dict)
nest.Connect(multimeter, neuron, "one_to_one")

#SIMULATION
nest.Simulate(400.0)

#GRAPHICS_SPIKES
dmm = nest.GetStatus(spikeDetector)[0]
dSD = nest.GetStatus(spikeDetector, keys = "events")[0]
evs = dSD["senders"]
ts = dSD["times"]

pylab.figure(1)
pylab.plot(ts,evs,".")
pylab.xlim(0, 400)
pylab.xlabel("time, ms")
pylab.ylabel("Spikes")

#GRAPHICS_CURRENTS
dmm = nest.GetStatus(multimeter)[0]

pylab.figure(2)
Currents = dmm["events"]["I_syn_ex"]
ts = dmm["events"]["times"]
pylab.plot(ts, Currents, label = "I_e = 0,0 pA")
pylab.xlabel("time, ms")
pylab.ylabel("I_syn_ex, pA")
pylab.legend()

frame = pd.DataFrame()
frame['times, ms'] = ts
frame['I_syn, pA'] = Currents
frame.to_csv("./I_syn_GEN.csv")

pylab.show()