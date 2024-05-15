"""
This script invokes phi-1.5, a ~1B parameter model, on a small prompt.

Demonstrated capabilities include:
- Model loading and invocation
- Terminating generation on key sequences
"""

import time
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

torch.set_default_device("cpu")

print("Loading model...")

model = AutoModelForCausalLM.from_pretrained(
    "microsoft/phi-1_5", torch_dtype=torch.float32
)
print("Loading tokenizer...")
tokenizer = AutoTokenizer.from_pretrained("microsoft/phi-1_5")
if tokenizer.pad_token is None:
    tokenizer.pad_token = tokenizer.eos_token

print("Tokenizing inputs...")
inputs = tokenizer(
    '''The assistant obeys the user completely and gives helpful, detailed answers to the user's questions. Each of its answers are finished with an <|endoftext|> token.

### Instruction:
Finish the code below by adding an empty return statement.
```python
def search_google(query:str)->list[str]:
   """
   Search Google for the query and return a list of 5 most relevant links.
   """
```


### Response:''',
    return_tensors="pt",
    return_attention_mask=False,
)

num_input_tokens = len(inputs["input_ids"][0])
print(f"Number of input tokens: {num_input_tokens}")

terminators = [
    # tokenizer.eos_token_id,
    # tokenizer.convert_tokens_to_ids("list"),
    # tokenizer.convert_tokens_to_ids("import"),
    # tokenizer.convert_tokens_to_ids("google"),
    # tokenizer.convert_tokens_to_ids("#"),
]

def gen_output(num_tokens):
    print(f"Generating output {num_tokens}...")
    t0 = time.time()
    outputs = model.generate(
        **inputs,
        max_new_tokens=num_tokens,
        pad_token_id=tokenizer.pad_token_id,
        eos_token_id=terminators,
        do_sample=True,
        temperature=0.6,
        top_p=0.9,
    )
    t1 = time.time()
    gen_time = t1 - t0
    num_output_tokens = len(outputs[0])
    print(f"Number of tokens after generation: {num_output_tokens}")
    print(
        f"{num_output_tokens - num_input_tokens} generated in {gen_time:.1f} s --> {(num_output_tokens - num_input_tokens)/gen_time:0.2f} tokens / second"
    )

    return gen_time

if __name__ == "__main__":
    for i in range(1,101):
        result = gen_output(i)
        with open("time_data.csv", "a") as f:
            f.write(f'{i}, {result}\n')
        
    