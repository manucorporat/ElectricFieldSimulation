Electric Field Simulation in GPU
=======================

This is an example of how to use OpenGL for physical simulations. All the simulation runs in parallel in the GPU using my own engine as the rendering layer. The potential and electric field is calculated for each pixel in screen, then several rules are applied to choose the output color.


![Electric Field](http://forzefield.com/electricimage.png)


## Download compiled app
[http://forzefield.com/ElectricFieldSimulation.zip](http://forzefield.com/ElectricFieldSimulation.zip)

## Where is the magic?
[Right here: simulation.frag](https://github.com/manucorporat/ElectricFieldSimulation/blob/master/Resources/simulation.frag)