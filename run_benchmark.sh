OUTPUT_FOLDER="output"
DATASETS_FOLDER="datasets/"

ALGOS=("liborbslam3_sp_torch-original-library.so"
"liborbslam3_sp_trt-original-library.so"
"libORB_SLAM3-original-library.so")

find $DATASETS_FOLDER -name "*.slam"|while read dataset; do
    output_dir="$OUTPUT_FOLDER/$(dirname ${dataset#$DATASETS_FOLDER})/$(basename $dataset .slam)"
    mkdir -p $output_dir
    for algo in "${ALGOS[@]}"; do
        algo_name=$(echo "${algo%.*}" | cut -d'-' -f1)
        if [ ! -f "${output_dir}/${algo_name}.log" ]; then
            ./build/bin/slambench -i $dataset -load "build/lib/$algo" -o "${output_dir}/${algo_name}.log"
        fi
    done
done
