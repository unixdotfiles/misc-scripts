#![deny(warnings)]
#![deny(missing_docs)]

//! Shows how much latency usleep has

use std::time::{Instant, Duration};

use libc::usleep;
use floating_duration::{TimeAsFloat};

fn main() {
    let mut all_deltas: Vec<Duration> = Vec::new();
    let second: Duration = Duration::new(1, 0);
    loop {
        let before: Instant = Instant::now();

        unsafe {
            usleep(second.as_micros() as _);
        }
        let delta: Duration = before.elapsed();
        let diff_from_second = delta - second;
        all_deltas.push(diff_from_second);
        println!("{:?}", diff_from_second.as_fractional_secs());
    }

}
