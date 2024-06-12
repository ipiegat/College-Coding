if ($ARGS.length -ne 1) {
    Write-Error "Please specify a directory to save output files."
    Write-Error "For example, run-test1.ps1 output"
    exit
}

$outputdir = $ARGS[0]
if ( -not (Test-Path $outputdir -PathType Container) ) {
    Write-Error "'$outputdir' is not a folder."
    exit
}

python rvsim.py input\t-add.txt > "$outputdir\t-add-out.txt"
python rvsim.py input\t-and.txt > "$outputdir\t-and-out.txt"
python rvsim.py input\t-sll.txt > "$outputdir\t-sll-out.txt"
python rvsim.py input\t-i.txt > "$outputdir\t-i-out.txt"
python rvsim.py input\t-beq.txt > "$outputdir\t-beq-out.txt"
python rvsim.py input\t-sw.txt > "$outputdir\t-sw-out.txt"
python rvsim.py input\t-hello.txt > "$outputdir\t-hello-out.txt"
python rvsim.py input\reversebytes.txt -a 0xA0B1C2D3 > "$outputdir\reversebytes-out.txt"
python rvsim.py input\fib.txt > "$outputdir\fib-out.txt"
python rvsim.py input\fact.txt > "$outputdir\fact-out.txt"
# python rvsim.py input\fib.txt -e 0 -a 47 > "$outputdir\fib-47-out.txt"
# may add more commands to compare with expected-output
