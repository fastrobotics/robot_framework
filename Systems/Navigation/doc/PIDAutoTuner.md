[Navigation System](System-Navigation.md)

- [PID Auto Tuner](#pid-auto-tuner)
  - [ToDo List](#todo-list)
  - [Overview](#overview)
  - [Tuning Algorithms](#tuning-algorithms)
- [Requirements](#requirements)
  - [Requirement: Dynamically compute PID Gains, Desired Output and Generated Set Point](#requirement-dynamically-compute-pid-gains-desired-output-and-generated-set-point)
  - [Requirement: Completely own the Tuning Process](#requirement-completely-own-the-tuning-process)
  - [Requirement: Report a Auto-Tuning State](#requirement-report-a-auto-tuning-state)
  - [Requirement: Provide Easy Mocking capabilities](#requirement-provide-easy-mocking-capabilities)
  - [Requirement: Provide easy interface for calibration parameter loading and saving](#requirement-provide-easy-interface-for-calibration-parameter-loading-and-saving)
  - [Requirement: Debuggable](#requirement-debuggable)
  - [Requirement: Support multiple Tuning Algorithms](#requirement-support-multiple-tuning-algorithms)
  - [Requirement: Tuning Algorithm State Machine](#requirement-tuning-algorithm-state-machine)
  - [Requirement: Tuner has defined stopping point](#requirement-tuner-has-defined-stopping-point)
- [Architecture](#architecture)
  - [Class Diagram](#class-diagram)
  - [State Machine](#state-machine)
  - [Sequence Diagrams](#sequence-diagrams)
  - [Integration Guide](#integration-guide)
    - [1. Include And Link The Module](#1-include-and-link-the-module)
    - [2. Configure And Start](#2-configure-and-start)
    - [3. Run The Control Loop](#3-run-the-control-loop)
    - [4. Read The Result](#4-read-the-result)
    - [Failure Diagnostics](#failure-diagnostics)
  - [Lessons Learned And Future Work](#lessons-learned-and-future-work)

# PID Auto Tuner
## ToDo List
- Delete the current RelayAutoTuneController content.
- 
## Overview
The PID Auto-Tuner module is designed to tune a system such that the values calibrated can be directly used in a PID Controller.

## Tuning Algorithms

The following algorithms are candidates for the PID Auto-Tuner. An algorithm
must both calculate candidate gains and apply/evaluate those gains against the
system before reporting successful tuning.

| Algorithm                                         | Description                                                                                                                                                                                                                                                  | Status                                |
| ------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------- |
| Bounded step response with closed-loop evaluation | Captures a baseline, applies a configured output step, measures the response, calculates candidate P/I/D gains, applies those gains, and evaluates tracking error. Candidate gains are adjusted and retried when the error exceeds the configured threshold. | **Implemented**                       |
| Relay feedback / relay auto-tune                  | Switches the output between two relay levels and derives gains from the resulting oscillation amplitude and period. The repository has a separate `RelayAutoTuneController`, but it is not currently an algorithm selectable by `PIDAutoTuner`.              | **Partially available**               |
| IMC / Lambda step-response tuning                 | Uses the measured process gain with configured dead time and desired closed-loop time constant, Lambda, to select conservative or aggressive gains. Candidate gains are then applied and evaluated in closed loop.                                           | **Implemented**                       |
| Ziegler-Nichols step-response tuning              | Estimates process gain, dead time, and time constant from a step response, then applies the Ziegler-Nichols tuning rules. It generally produces more aggressive gains than IMC/Lambda tuning.                                                                | **Not implemented**                   |
| Ziegler-Nichols ultimate-gain tuning              | Increases loop gain until sustained oscillation is observed, then derives gains from ultimate gain and oscillation period.                                                                                                                                   | **Not implemented in `PIDAutoTuner`** |
| Cohen-Coon tuning                                 | Uses a first-order-plus-dead-time model and is intended to compensate for process dead time, often at the cost of more aggressive behavior.                                                                                                                  | **Not implemented**                   |

The current implementation supports bounded step-response and IMC/Lambda
tuning, selected by `PIDAutoTuningAlgorithm`. The selector is part of the
public configuration API. Each tuning operation applies positive and negative
output steps, measures both responses, and averages their process gains before
calculating one set of PID gains. Unsupported algorithms are rejected until
their implementations are added. IMC/Lambda additionally requires process
dead time and the desired closed-loop time constant:

```cpp
config.set_algorithm(PIDAutoTuningAlgorithm::IMC_LAMBDA);
config.set_imc_parameters(
  0.2, // process dead time in seconds
  2.0); // desired closed-loop time constant, Lambda, in seconds
```

# Requirements
Each Requirement will have:
- A status if it was Met/Did Not Meet (and justification why)
- The name and description
- Evidence showing that it was met
## Requirement: Dynamically compute PID Gains, Desired Output and Generated Set Point
*Met?* Partially met.

*Description*

The first implementation computes PID gains from a bounded step-response
measurement and exposes the generated set point and desired output through
`PIDAutoTunerOutput`. These values can be displayed or stored by the caller.

*Evidence*

`PIDAutoTunerOutput` contains `set_point`, `command_value`, `K_P`, `K_I`, and
`K_D`. `test_PIDAutoTuner.cpp` verifies that a valid response produces nonzero
gains.

## Requirement: Completely own the Tuning Process
*Met?* Partially met.

*Description*

The implementation owns baseline capture, generated target set point, output
step, response measurement, candidate PID evaluation, gain iteration, timeout
handling, and completion/failure transitions. The selected algorithm and its
configuration are supplied before tuning.

*Evidence*

After `start_tuning()`, the first sensor sample establishes the baseline and
the tuner generates the next set point. `update()` advances the algorithm and
drives the output command without another caller-selected set point.

## Requirement: Report a Auto-Tuning State
*Met?* Met for the first implementation.

*Description*

The Auto-Tuner reports `IDLE`, `TUNING`, `COMPLETE`, or `FAILED`. The tuning
algorithm also reports `CAPTURE_BASELINE`, `APPLY_STEP`, `MEASURE_RESPONSE`,
`EVALUATE_PID`, `COMPLETE`, or `FAILED`.

*Evidence*

`PIDAutoTunerOutput::state`, `algorithm`, and `algorithm_state` expose the
selected algorithm and both state machines. Tests cover tuning, completion,
IMC/Lambda selection, gain evaluation, iteration, and timeout failure.

## Requirement: Provide Easy Mocking capabilities
*Met?* Not implemented in this module yet.

*Description*

The Auto-Tuner should be capable of easily mocking behaviour.  Intent here is to validate any UI/integration components without negatively affecting a live system.  Enabling/Disabling this mode should be an easy switch, and no extra configuration required for the user beyond the required configuration for the production version of the Auto-Tuner.

*Evidence*

The existing relay controller mock remains separate. A common tuner interface
and an implementation-selection strategy are still required for this module.

## Requirement: Provide easy interface for calibration parameter loading and saving
*Met?* Partially met.

*Description*

The tuner accepts initial PID parameters through `set_parameters()` and
returns the calculated parameters through `get_tuned_config()`.

*Evidence*

`get_tuned_config()` returns a `PIDControllerConfig` after successful tuning.
Loading and saving a persistent file format is not implemented yet.

## Requirement: Debuggable
*Met?* Met for the first implementation.

*Description*

The Auto-Tuner should be capable of easy inspection of the state of the module.  

*Evidence*

`pretty()` reports configuration, main state, algorithm state, set point,
sensor value, and calculated gains.

## Requirement: Support multiple Tuning Algorithms
*Met?* Partially met.

*Description*

The Auto-Tuner should be capable of potentially multiple different tuning algorithms that could be enabled by the user.

*Evidence*

The implementation currently supports bounded step-response and IMC/Lambda
algorithms. The configuration selector and dispatch boundary allow additional
algorithms to be added later.

## Requirement: Tuning Algorithm State Machine
*Met?* Met for the first implementation.

*Description*

If a tuning algorithm has a series of steps it must go thru, it should follow a sub-state machine (while the main Auto-Tuner is in state `TUNING`).

*Evidence*

`PIDAutoTunerAlgorithmState` tracks baseline capture, step application,
response measurement, candidate PID evaluation, completion, and failure while
the main state is `TUNING`. Both supported algorithms use this same lifecycle;
IMC/Lambda changes the gain calculation after the response is measured. When
evaluation error exceeds the configured threshold, the tuner adjusts the
candidate gains and retries until the iteration limit is reached.

## Requirement: Tuner has defined stopping point
*Met?* As implemented currently, this requirement is not yet.

*Description*

The module should have various configuration options and automated checks that ensure that it is progressing towards a goal.  The module should quickly inform the user that if the tuning process isn't making progress, it should fail and indicate the reason why.

*Evidence*


# Architecture
![](../../../Legend.png)
## Class Diagram
![](puml/PIDAutoTunerClassDiagram.png)

## State Machine
The state machine source is [PIDAutoTunerStateMachine.puml](puml/PIDAutoTunerStateMachine.puml).
The main tuner remains in `TUNING` while its algorithm progresses through
baseline capture, step application, response measurement, and PID evaluation.
An unacceptable evaluation retries with adjusted gains until the configured
iteration limit is reached.

## Sequence Diagrams
![](puml/PIDAutoTunerSequenceDiagram.png)

The sequence includes the generated setpoint and output command flow. The
application must send `output.command_value` to the system and feed the
resulting sensor response back to the tuner. Candidate gains are applied and
evaluated before the tuner reports `COMPLETE`.

## Integration Guide

The application owns the `PIDAutoTuner` object and is responsible for calling
its lifecycle methods from the control loop. The tuner owns the tuning state,
generates the next set point, and produces the command that the application
should send to the system under test.

### 1. Include And Link The Module

Include the public header and link the `pid_auto_tuner_Controller` target in
the application target:

```cmake
target_link_libraries(my_application pid_auto_tuner_Controller)
```

```cpp
#include <ControllerTuner/PIDAutoTuner/PIDAutoTuner.hpp>
```

### 2. Configure And Start

Configure the initial PID values and the step-response parameters before
starting. The initial PID values are optional tuning context for the current
algorithm, but both parameter groups must be supplied and valid.

```cpp
using namespace fast::rf::NavigationSystem::Controller;
using namespace fast::rf::NavigationSystem::ControllerTuner;

PIDAutoTuner tuner;
PIDAutoTunerConfig config;

config.set_parameters(
  10.0,  // maximum output
  -10.0, // minimum output
  0.0,   // initial K_P
  0.0,   // initial K_I
  0.0,   // initial K_D
  1.0);  // sensor scale factor

config.set_tuning_parameters(
  2.0,  // output step applied to the system
  1.0,  // generated setpoint step
  1.0,  // settle time in seconds
  3.0,  // response timeout in seconds
  0.5,  // minimum measured response
  0.05, // acceptable maximum tracking error
  1.0,  // evaluation duration in seconds
  3);   // maximum candidate-gain iterations

if (!tuner.set_config(config) || !tuner.init() || !tuner.start_tuning()) {
  // Do not start the tuning loop when configuration or initialization fails.
}
```

### 3. Run The Control Loop

Provide sensor samples with timestamps and call `update()` using the same
monotonic time base. The first sensor sample captures the baseline. The tuner
then generates positive and negative setpoints in sequence and, on `update()`,
publishes each output command.

```cpp
while (tuner.get_state() == AutoTunerState::TUNING) {
  double now_sec = get_monotonic_time_seconds();
  double sensor_value = read_sensor();

  if (!tuner.new_sensor_input(sensor_value, now_sec) || !tuner.update(now_sec)) {
    break;
  }

  PIDAutoTunerOutput* output = tuner.get_output();
  send_command(output->command_value);
  display_set_point(output->set_point);
  display_state(output->state, output->algorithm_state);
  delete output;
}
```

`get_output()` returns a newly allocated snapshot. The caller owns it and must
delete it after consuming the values. The command should be sent to the
system under test on every output update; the tuner does not publish directly
to hardware.

### 4. Read The Result

When the state becomes `COMPLETE`, the output contains the calculated gains
and `get_tuned_config()` returns a `PIDControllerConfig` suitable for use by
the PID controller.

```cpp
if (tuner.tuning_succeeded()) {
  PIDControllerConfig tuned_config = tuner.get_tuned_config();
  save_pid_configuration(tuned_config.get_K_P(), tuned_config.get_K_I(),
               tuned_config.get_K_D());
} else if (tuner.get_state() == AutoTunerState::FAILED) {
  report_tuning_failure();
}
```

The `TUNING` output may have zero `K_P`, `K_I`, and `K_D` values. They are
populated after both directional step responses produce a candidate. The
candidate gains are then applied to the live system during the `EVALUATE_PID`
algorithm state.
The tuner records the maximum absolute tracking error for diagnostics and
checks the final absolute tracking error for acceptance. It reaches `COMPLETE`
only when that final error is less than or equal to
`acceptable_error_threshold`. If the final error is larger, the tuner adjusts
the candidate gains and retries while the main state remains `TUNING`; after
`max_tuning_iterations` unsuccessful evaluations it reaches `FAILED`.

### Failure Diagnostics

When tuning fails, `PIDAutoTunerOutput` contains a structured explanation:

| Field                   | Description                                                            |
| ----------------------- | ---------------------------------------------------------------------- |
| `failure_reason`        | Machine-readable `PIDAutoTunerFailureReason` enum value.               |
| `failure_reason_string` | Printable name of the enum value.                                      |
| `failure_attribute`     | The measured value or configuration attribute that caused the failure. |
| `failure_remediation`   | Suggested corrective action for the application or operator.           |

The current failure reasons are `INVALID_CONFIGURATION`, `RESPONSE_TIMEOUT`,
`INSUFFICIENT_RESPONSE`, `TRACKING_ERROR_EXCEEDED`,
`TUNING_ITERATION_LIMIT`, and `UNSUPPORTED_ALGORITHM`. A successful or reset
controller reports `NONE` and clears the related diagnostic strings.

## Lessons Learned And Future Work

This section records the tuning investigation from September 2026. It is
intended to preserve the observations, terminology, configuration experiments,
implementation changes, and unresolved design questions that are easy to lose
when tuning is performed against a real robot.

### The Most Important Distinction: Output Versus Setpoint

The tuner has two independent step parameters:

```text
output_step       actuator command applied to the plant
set_point_step    change requested in the measured-sensor domain
```

The tuner computes the plant response from the output step and creates the
generated setpoint from the setpoint step:

```text
setpoint = baseline_sensor + set_point_step
response = measured_sensor - baseline_sensor
process_gain = response / output_step
```

The code does not automatically make these values equal. If the robot's
system contract uses the same units for both values, configure them with the
same magnitude. For example:

```cpp
config.set_tuning_parameters(
   30.0,  // output step
   30.0,  // setpoint step, because the contract uses the same units
   5.0,
   20.0,
   0.5,
   5.0,
   20.0,
   2);
```

If the values use different units, they should remain separate. A common
example is an actuator command in motor units and a setpoint in radians per
second. In that case, setting both to `30.0` would be wrong. The important
point is that the distinction must be deliberate and documented at the
integration boundary.

`sensor_scale` is a third concept. It converts incoming sensor samples into
the units used by the tuner:

```text
tuner_sensor = sensor_scale * incoming_sensor
```

It does not convert `output_step` or `set_point_step`, and it does not make
the output and setpoint units match.

### What The Original Failure Meant

`TUNING_ITERATION_LIMIT` does not mean that the forward or reverse plant sweep
failed. It means that the candidate PID controller failed its evaluation the
configured number of times. The original retry logic multiplied all candidate
gains by `1.5` after each unsuccessful evaluation:

```text
failed evaluation -> Kp, Ki, Kd multiplied by 1.5 -> retry
```

This can make a noisy or physically unstable system progressively more
aggressive. Increasing `max_tuning_iterations` is therefore not automatically
the correct response. It gives the tuner permission to try more candidates,
but it can also make the next candidates harder on the robot.

The final `command_value = 0.0` in a failure log is a safety action performed
by `fail_tuning()`. It is not evidence that the application stopped sending
commands before the failure. To diagnose the actual failing command, log the
output while `algorithm_state == EVALUATE_PID`, before the failure transition.

### Observed Robot Behavior

The robot exhibited an effective actuator deadband. Commands below roughly
`25` did not reliably produce motion. This created a difficult mismatch:

```text
small PID command, for example -1 to -5 -> no useful motion
large identification command, for example -30 -> motion
```

With a one-unit setpoint step, a candidate such as `K_P = 0.5` naturally
produced a proportional command close to `-0.5`. Even with integral action,
the command could remain far below the movement threshold while the tracking
error stayed close to one unit. The tuner then correctly rejected the
candidate according to its configured threshold, but the candidate was not
able to exercise the real plant because of the deadband.

The environment also had a smooth or dynamic floor. The robot could move or
jump unexpectedly, and the sensor signal contained visible noise around zero.
This made derivative action and hard command switching especially risky.

### Bidirectional Identification

The tuner was changed from a positive-only plant step to one operation that
performs both directions:

```text
capture baseline
apply positive output step
measure positive response
brief zero-command handoff
apply negative output step
measure negative response
calculate one candidate from both responses
evaluate the candidate PID controller
```

The positive and negative responses are normalized by their signed input
directions and averaged into one process gain. This makes the result less
dependent on one direction and avoids requiring the operator to run two
separate tuning sessions.

The `max_tuning_iterations` value does not count the positive and negative
plant sweeps. It counts unsuccessful closed-loop PID evaluations after the
candidate has been calculated.

### Why Large Commands Caused Oscillation

To work around the deadband, the evaluation path was temporarily changed to
raise small nonzero PID commands to the magnitude of the identification step.
With `output_step = 30`, a PID request of `-4` became `-30`. This allowed the
robot to move, but it also created bang-bang behavior:

```text
small noisy PID request -> full -30 command
small sign change       -> full +30 command
```

This explains the logs containing many repeated `+30` and `-30` commands. A
large command floor is not a normal PID controller. It is a relay-like
controller, and it should not be held for a long evaluation window on a robot
that can move unpredictably.

The current implementation limits this compensation to the startup portion
of evaluation. It applies the sweep magnitude only until the measured sensor
response reaches `minimum_response`, then returns to the calculated PID
command. It also prevents a command in the final evaluation from changing to
the opposite setpoint direction. These changes reduce command reversals, but
they do not make the deadband problem disappear. They are pragmatic temporary
behavior, not a complete actuator model.

### Error Acceptance And Why It Was Confusing

The tuner has these related values:

```text
tracking_error          current setpoint minus current sensor value
maximum_tracking_error  largest observed absolute error for diagnostics
acceptable_error_threshold
                tolerance used to decide success
evaluation_time_sec     duration of the candidate evaluation
settle_time_sec         plant-response wait time and evaluation settling time
```

The observed robot logs showed two different kinds of error:

1. A large transient immediately after the deadband-breaking command.
2. A smaller but persistent error after the robot moved toward the target.

Using the maximum error across the whole window made the initial transient
determine the result, even when later behavior looked reasonable. A temporary
implementation experimented with average post-settle error, but the current
implementation was deliberately simplified again. The current acceptance
rule is straightforward:

```text
at evaluation expiry:
   success if abs(current tracking error) <= acceptable_error_threshold
   otherwise retry or fail
```

`maximum_tracking_error` remains diagnostic data. This simple rule is easier
to explain, but it has an important limitation: a controller can pass through
the target briefly and still be accepted if the final sample happens to be
inside the threshold. Conversely, a controller that is mostly good can fail
if its final sample is noisy. A future implementation should choose one
explicit policy and test it with recorded robot data, such as:

```text
final error after a settle period
average absolute error over a final window
maximum error plus a settling or oscillation criterion
```

The policy should be visible in the output and documentation. It should not
silently change between experiments.

### Recommended Configuration For The Current Rate Tuner

The following is a conservative starting point for a system whose command and
setpoint units are both the same and whose actuator needs approximately `30`
to move:

```cpp
config.set_parameters(
   100.0,  // maximum actuator output
   -100.0, // minimum actuator output
   0.0,    // initial K_P
   0.0,    // initial K_I
   0.0,    // initial K_D
   1.0);   // sensor scale

config.set_algorithm(PIDAutoTuningAlgorithm::IMC_LAMBDA);
config.set_imc_parameters(
   0.0,    // dead time; leaves derivative gain at zero
   15.0);  // larger Lambda gives slower, less aggressive gains

config.set_tuning_parameters(
   30.0,   // output step: positive and negative plant identification
   30.0,   // setpoint step in the same contract units
   5.0,    // plant settle time
   20.0,   // response timeout
   0.5,    // minimum measured response
   5.0,    // acceptable final tracking error
   20.0,   // candidate evaluation duration
   2);     // unsuccessful candidate evaluations allowed
```

This configuration is not universally correct. It is a documented starting
point based on the observed system. Adjust one value at a time and record the
result. In particular:

- Keep `output_step` high enough to overcome static friction, but below a
  mechanically safe command.
- Set `set_point_step` to the actual contract displacement, not automatically
  to the output command unless their units are truly identical.
- Increase `lambda_sec` to make IMC/Lambda tuning slower and less aggressive.
- Keep `dead_time_sec` at zero while the feedback signal is noisy; this makes
  the generated derivative gain zero.
- Use a threshold larger than the real measurement noise and smaller than an
  unacceptable control error.
- Increase `evaluation_time_sec` only when the system genuinely needs more
  time to settle. It does not reduce gains or slow the controller.
- Keep `response_timeout_sec` greater than or equal to `settle_time_sec`.
- Keep `max_output` and `min_output` symmetric when both movement directions
  are required.
- Treat `max_tuning_iterations` as a safety budget, not as a cure for a bad
  candidate.

### Derivative Term Findings

In IMC/Lambda mode, the derivative term is calculated from configured dead time:

```text
derivative_time = time_constant * dead_time /
            (2 * time_constant + dead_time)
K_D = K_P * derivative_time
```

Therefore `dead_time_sec = 0.0` intentionally produces `K_D = 0.0`. This was
useful during testing because the noisy floor and noisy feedback made D action
likely to amplify measurement noise. A nonzero D term should only be restored
using a measured dead time and a filtered sensor signal. The current tuner
does not implement derivative filtering.

### Saving The Generated Configuration

The generated gains are available in two places:

```cpp
PIDAutoTunerOutput* output = tuner.get_output();
double kp = output->K_P;
double ki = output->K_I;
double kd = output->K_D;
delete output;

Controller::PIDControllerConfig tuned = tuner.get_tuned_config();
```

Only use `get_tuned_config()` as the active controller configuration after the
tuner reports `COMPLETE`. During `TUNING`, the output may contain zero gains or
an intermediate candidate that has not passed evaluation. The repository does
not currently provide a file-format persistence API; the application must
serialize the gains and limits using its own configuration mechanism.

The application should persist at least:

```text
K_P, K_I, K_D
max_output, min_output
sensor_scale
algorithm and tuning date
sensor and actuator units
```

For reproducibility, also save the tuning parameters, the observed positive
and negative responses, the selected Lambda/dead-time values, and the final
diagnostic values. A gain file without units is not sufficient to safely reuse
the result.

### Recommended Logging For The Next Trial

Log one record per sensor/update cycle during tuning. At minimum, include:

```text
wall-clock time
monotonic time
main state
algorithm state
baseline sensor
setpoint
sensor input after scaling
response
tracking error
command value
K_P, K_I, K_D
maximum tracking error
failure reason and attribute
```

The command must be logged before the failure transition, because failure
handling intentionally replaces it with zero. When inspecting the log, first
separate the phases:

```text
MEASURE_RESPONSE  plant identification
EVALUATE_PID      closed-loop candidate test
FAILED            safety stop, command forced to zero
```

This avoids interpreting the final safety command as the command that caused
the failure.

### Angle Control: Recommended Future Architecture

The robot's current trajectory controller feeds measured angular velocity into
the PID controller and writes the PID result to the angular command:

```text
desired angular rate -> PID -> actuator command
measured angular rate ----------------^
```

This is appropriate for an inner rate loop, but it is not a direct angle
controller. If the actual goal is to hold or reach an orientation, use a
cascaded controller:

```text
desired angle
   -> outer angle controller
   -> bounded angular-rate setpoint
   -> existing inner angular-rate PID
   -> actuator command
```

The outer loop should:

- read yaw or heading from the pose orientation;
- wrap the angle error to `[-pi, pi]`;
- use a small angle deadband or hysteresis;
- limit the generated angular-rate setpoint;
- start with P-only control;
- add I only for a demonstrated persistent bias;
- avoid D until the angle signal is filtered and its noise is understood.

The existing `PIDAutoTuner` should remain focused on tuning the inner rate
loop. An angle loop has different units, dynamics, safety limits, and useful
step sizes. Reusing the rate-tuner configuration directly for angle tuning
would recreate the output/setpoint ambiguity documented above.

### Concrete Future Work Items

The next implementation pass should consider these items in order:

1. Define the actuator contract, including command units, static-friction
  threshold, maximum safe output, and whether positive and negative motion
  have equal authority.
2. Define the controlled variable explicitly: angular rate, angle, or a
  cascaded angle/rate pair.
3. Add an explicit actuator deadband configuration rather than using
  `output_step` as both an identification step and a minimum evaluation
  command.
4. Implement deadband hysteresis or a proper friction-compensation model so
  noise cannot turn into repeated full-size reversals.
5. Add derivative filtering and expose the filtered signal or D term for
  diagnostics.
6. Replace gain escalation by a bounded candidate search. A failed candidate
  should not automatically multiply all gains by `1.5` without considering
  overshoot, saturation, and direction.
7. Make evaluation acceptance explicit and configurable, preferably with a
  final settling window and an oscillation/saturation guard.
8. Add recorded-data tests that reproduce the noisy floor behavior without
  requiring the physical robot.
9. Add a persistence format with units, tuning metadata, and validation on
  load.
10. Add a cascaded angle/rate controller at the trajectory-controller boundary
   rather than replacing the rate measurement with angle data in the current
   tuner.

### Current Status Summary

The current module is useful as an experimental, bounded step-response tuner
for a rate loop. It can perform a positive and negative characterization in
one operation, calculate candidate gains, expose output diagnostics, and stop
with a structured failure reason. It is not yet a robust production tuner for
a noisy dynamic robot with actuator deadband. In particular, the deadband
compensation and final evaluation behavior should be treated as provisional,
and the resulting gains should not be deployed without a controlled-motion
test and an independent safety limit.
