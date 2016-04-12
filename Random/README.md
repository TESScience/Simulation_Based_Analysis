Development of very fast pseudo-random number generators for parallel processing.

These are combinations of Fibonnaci, linear congruential and and MPWD's "safe prime"
method.

- `randa` is a classic long-lag (24/55) additive Fibonnaci generator.
- `calrissian` is a safe prime plus linear congruential.
- `sqarission` is a small safe prime squared plus linear conguential.
- `squafib` is a small safe prime squared plus minimal additive Fibonnaci.
- `warpspeed` is a classic long-lag (32/43/57/64) additive Fibonnaci generator. It is designed so that batches of 64 random numbers can be generated at a time with a warp.

`random` is a test command that writes random binary numbers to stdout.
