#!/usr/bin/env python3

import json

def CommandLineParser():
    from argparse import ArgumentParser
   
    parser = ArgumentParser(prog='data_template_generator.py', usage='%(prog)s [options]', description='Generate a template json file.')

    parser.add_argument("-i", metavar="--input_file", dest="in_file_name", type=str,
            help="<MANDATORY> : Input Json file to be parsed.")
    parser.add_argument("-o", metavar="--output_file", dest="out_file_name", default='default_template.json', type=str,
            help="[OPTIONAL] : Generated json file will be stored with the given file name. Defalut file = default_template.json")
    parser.add_argument("-n", metavar="--root_node", dest="root_node", default='frames', type=str,
            help="[OPTIONAL] : Root node of the json. Default root_node = 'frames'")

    args = parser.parse_args()
    if not args.in_file_name:
        parser.print_help()
        return 
    else:
        return [args.in_file_name, args.out_file_name, args.root_node]

def ParseFile(in_file, out_file='default_template.json', root_node='frames'):
    print('Reading from file : ', in_file, '\nRoot node : ', root_node)
    with open(in_file) as f:
        data = json.load(f)
        template_dict ={}
        JsonTemplateGenerator(data, root_node, template_dict)
        json_out = json.dumps(template_dict, indent=4, sort_keys=True, separators=(',', ': '))
        print('Writing to file : ', out_file)
        with open(out_file, 'w') as o_f:
            o_f.write(json_out)


def JsonTemplateGenerator(json_data, key, template_dict) :
    if (type(json_data[key]) is list):
        if type(json_data[key][0]) is dict:
            nested_data = json_data[key][0].keys()
            temp_data = json_data[key][0]
            template_dict[key] = list(nested_data)
            [JsonTemplateGenerator(temp_data, item, template_dict) for item in nested_data]     
    if type(json_data[key]) is dict:
        template_dict[key] = list(json_data[key].keys())
 
def main():
    val = CommandLineParser()
    if val:
        ParseFile(in_file=val[0], out_file=val[1], root_node=val[2])

if __name__== "__main__":
    main()
