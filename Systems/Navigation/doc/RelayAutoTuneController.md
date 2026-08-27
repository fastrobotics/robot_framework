# Relay Auto-Tune Configuration

The relay auto-tuner deliberately switches the command between two levels so
it can observe how the system responds. The four output-related parameters
define that command band.

```text
                         output command
                              ^
                              |
 max_output ------------------+-------------------- upper allowed command
                              |
                    high = bias + relay_amplitude
                              |<-- relay_amplitude -->|
                              |
 bias ------------------------+-------------------- center of relay band
                              |
                    low  = bias - relay_amplitude
                              |<-- relay_amplitude -->|
                              |
 min_output ------------------+-------------------- lower allowed command
                              +--------------------->
```

The tuner alternates between:

```text
high_command = bias + relay_amplitude
low_command  = bias - relay_amplitude
```

`relay_amplitude` is the distance from `bias` to either command level. The
peak-to-peak command change is therefore `2 * relay_amplitude`.

`max_output` and `min_output` are absolute command limits. The configuration
is valid only when the complete relay band fits inside those limits:

```text
min_output <= bias - relay_amplitude
min_output <= bias + relay_amplitude
bias + relay_amplitude <= max_output
```

For example:

```cpp
config.set_parameters(
    5.0,   // max_output
    -5.0,  // min_output
    2.0,   // relay_amplitude
    0.0,   // bias
    1.0,   // sensor scale
    4);    // required cycles
```

This produces commands of `+2.0` and `-2.0`, both within the `[-5.0, 5.0]`
output range.

With a nonzero bias:

```cpp
config.set_parameters(
    10.0,  // max_output
    0.0,   // min_output
    2.0,   // relay_amplitude
    4.0,   // bias
    1.0,
    4);
```

the relay switches between `2.0` and `6.0`. The bias is useful when the plant
needs a positive steady command to remain active, such as overcoming gravity
or static friction.

The output limits do not force the relay command to those limits. They define
the permitted range, while `bias` and `relay_amplitude` define the two actual
test commands. If either relay level falls outside the range, configuration
validation fails.