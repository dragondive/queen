"""Plots the solution times for Queen problem by language and n."""

import argparse
import os

import pandas
from matplotlib import pyplot


def parse_arguments() -> argparse.Namespace:
    """Parse command-line arguments."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--input-csv-file',
        required=True,
        help='CSV file containing the solution times for Queen problem',
    )
    parser.add_argument(
        '--output-svg-files-path',
        required=True,
        help='Path to store the output SVG files',
    )
    return parser.parse_args()


def prepare_plot_data(
    data: pandas.DataFrame,
) -> pandas.core.groupby.SeriesGroupBy:
    """Prepare the data for plotting."""
    averaged_data = data.groupby(['language', 'n']).mean().reset_index()
    averaged_data.set_index('n', inplace=True)
    return averaged_data.groupby('language')['time']


def plot_data_and_save(data, output_path) -> None:
    """Plot the data and saves the plots as SVG files."""
    pyplot.figure()
    data.plot(
        xlabel='n',
        ylabel='time (ms)',
        title='Queen problem solution time by language (log scale)',
        legend=True,
        logy=True,
    )
    pyplot.savefig(f'{os.path.join(output_path, "queen_log_scale_plot.svg")}')

    pyplot.figure()
    data.plot(
        xlabel='n',
        ylabel='time (ms)',
        title='Queen problem solution time by language (linear scale)',
        legend=True,
    )
    pyplot.savefig(f'{os.path.join(output_path, "queen_linear_scale_plot.svg")}')


def main():
    """Plot data from CSV file into SVG format."""
    args = parse_arguments()
    data = pandas.read_csv(args.input_csv_file)
    plot_data = prepare_plot_data(data)
    full_output_path = os.path.abspath(os.path.normpath(args.output_svg_files_path))
    os.makedirs(full_output_path, exist_ok=True)
    plot_data_and_save(plot_data, full_output_path)


if __name__ == '__main__':
    main()
