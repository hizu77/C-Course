#include "Bitmap.h"
#include "Parser.h"
#include "Scaning.h"
#include "Output.h"

void Output(int argc,char** argv) {
    Args args = Parse(argc, argv);
    if (!args.correct) {
        std::cerr << "Incorrect input";
        return;
    }
    Field sand_pile;
    sand_pile.ScanParameters(args.filename);
    sand_pile.Import(args.filename);
    sand_pile.ScanRealParams();
    std::string Output = args.output_directory;
    Output += "\\image";
    if(args.frequency == 0) {
        if (args.max_Iterations == 0) {
            while (sand_pile.flag_of_iterations) {
                sand_pile.Iteration();
            }
        } else {
            for (int i = 0; i < args.max_Iterations; ++i) {
                sand_pile.Iteration();
            }
        }
        sand_pile.Output();
        Output += ".bmp";
        std::cout << Output;
        ConvertToBmp(sand_pile.real_width, sand_pile.real_height, sand_pile.real_x, sand_pile.real_y, sand_pile.pixels, Output);
    } else {
        if (args.max_Iterations == 0) {
            int num_of_iteration = 0;
            while (sand_pile.flag_of_iterations) {
                sand_pile.Iteration();
                if (num_of_iteration % args.frequency == 0) {
                    std::string temp_Output = Output;
                    temp_Output += std::to_string(num_of_iteration);
                    temp_Output += ".bmp";
                    std::cout << temp_Output << '\n';
                    ConvertToBmp(sand_pile.real_width, sand_pile.real_height, sand_pile.real_x, sand_pile.real_y, sand_pile.pixels, temp_Output);
                }
                ++num_of_iteration;
            }
        } else {
            for (int i = 0; i < args.max_Iterations; ++i) {
                sand_pile.Iteration();
                if (i % args.frequency == 0) {
                    std::string temp_Output = Output;
                    temp_Output += std::to_string(i);
                    temp_Output += ".bmp";
                    std::cout << temp_Output << '\n';
                    ConvertToBmp(sand_pile.real_width, sand_pile.real_height, sand_pile.real_x, sand_pile.real_y, sand_pile.pixels, temp_Output);
                }
            }
        }
    }

    for (int64_t i = 0; i < sand_pile.size_y / 2; ++i) {
        delete sand_pile.pixels[i];
    }
    delete sand_pile.pixels;

    std::cout << "\nFile created!!!";
}
