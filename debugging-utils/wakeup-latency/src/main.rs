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

use std::time::{Duration, Instant};

use floating_duration::TimeAsFloat;
use libc::usleep;

use stats::OnlineStats;

use clap::{app_from_crate, crate_authors, crate_description, crate_name, crate_version, Arg};

const SECOND: Duration = Duration::from_secs(1);

fn main() {
    let matches = app_from_crate!()
        .arg(
            Arg::with_name("count")
                .short("c")
                .long("count")
                .takes_value(true),
        )
        .get_matches();

    let count_iter: Box<dyn Iterator<Item = u32>> =
        matches.value_of("count").map_or(Box::new(0..), |v: &str| {
            let parsed: u32 = v.parse::<u32>().expect("count must be an integer");
            Box::new(0..parsed)
        });

    let mut stat_container = OnlineStats::new();
    //    signal_hook::flag::register(signal_hook::SIGINFO, display_stats);
    for _ in count_iter {
        let before: Instant = Instant::now();

        unsafe {
            let _ = usleep(SECOND.as_micros() as _);
        }
        let delta: Duration = before.elapsed();
        let diff_from_second = delta - SECOND;
        stat_container.add(diff_from_second.as_nanos());
        println!(
            "{} (mean: {} stddev: {})",
            diff_from_second.as_fractional_secs(),
            stat_container.mean() / SECOND.as_nanos() as f64,
            stat_container.stddev() / SECOND.as_nanos() as f64
        );
    }
}
