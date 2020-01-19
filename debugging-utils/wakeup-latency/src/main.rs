#![deny(warnings)]
#![deny(missing_docs)]
#![deny(anonymous_parameters)]
#![deny(bare_trait_objects)]
#![deny(elided_lifetimes_in_paths)]
#![deny(missing_copy_implementations)]
#![deny(missing_debug_implementations)]
#![deny(single_use_lifetimes)]
#![deny(trivial_casts)]
#![deny(trivial_numeric_casts)]
#![deny(unreachable_pub)]
#![deny(unused_extern_crates)]
#![deny(unused_import_braces)]
#![deny(unused_qualifications)]
#![deny(unused_results)]
#![deny(variant_size_differences)]

//! Shows how much latency usleep has

use std::time::{Instant, Duration};

use libc::usleep;
use floating_duration::TimeAsFloat;

fn main() {
    let second: Duration = Duration::new(1, 0);
    loop {
        let before: Instant = Instant::now();

        unsafe {
            let _ = usleep(second.as_micros() as _);
        }
        let delta: Duration = before.elapsed();
        let diff_from_second = delta - second;
        println!("{:?}", diff_from_second.as_fractional_secs());
    }

}
