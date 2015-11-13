--
-- PostgreSQL database dump
--

-- Dumped from database version 9.4.5
-- Dumped by pg_dump version 9.4.5
-- Started on 2015-11-13 11:07:41 CET

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 7 (class 2615 OID 16395)
-- Name: core; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA core;


ALTER SCHEMA core OWNER TO jolo;

--
-- TOC entry 8 (class 2615 OID 16396)
-- Name: stat; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA stat;


ALTER SCHEMA stat OWNER TO jolo;

--
-- TOC entry 272 (class 3079 OID 11895)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2668 (class 0 OID 0)
-- Dependencies: 272
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- TOC entry 271 (class 3079 OID 16386)
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- TOC entry 2669 (class 0 OID 0)
-- Dependencies: 271
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


SET search_path = core, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 174 (class 1259 OID 16397)
-- Name: administration_method; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE administration_method (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    channel_into_patient_id integer NOT NULL,
    CONSTRAINT administration_method_name_check CHECK ((length(name) > 1))
);


ALTER TABLE administration_method OWNER TO jolo;

--
-- TOC entry 175 (class 1259 OID 16405)
-- Name: administration_method_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE administration_method_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE administration_method_id_seq OWNER TO jolo;

--
-- TOC entry 2670 (class 0 OID 0)
-- Dependencies: 175
-- Name: administration_method_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE administration_method_id_seq OWNED BY administration_method.id;


--
-- TOC entry 254 (class 1259 OID 16999)
-- Name: age_class; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE age_class (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE age_class OWNER TO jolo;

--
-- TOC entry 253 (class 1259 OID 16997)
-- Name: age_class_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE age_class_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE age_class_id_seq OWNER TO jolo;

--
-- TOC entry 2671 (class 0 OID 0)
-- Dependencies: 253
-- Name: age_class_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE age_class_id_seq OWNED BY age_class.id;


--
-- TOC entry 176 (class 1259 OID 16407)
-- Name: campaign; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE campaign (
    id integer NOT NULL,
    project_id integer NOT NULL,
    name text NOT NULL,
    start_date date DEFAULT ('now'::text)::date NOT NULL,
    end_date date DEFAULT ('now'::text)::date NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT campaign_check CHECK ((end_date >= start_date)),
    CONSTRAINT campaign_name_check CHECK ((length(name) > 1))
);


ALTER TABLE campaign OWNER TO jolo;

--
-- TOC entry 177 (class 1259 OID 16418)
-- Name: campaign_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE campaign_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE campaign_id_seq OWNER TO jolo;

--
-- TOC entry 2672 (class 0 OID 0)
-- Dependencies: 177
-- Name: campaign_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE campaign_id_seq OWNED BY campaign.id;


--
-- TOC entry 264 (class 1259 OID 17126)
-- Name: cgi; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE cgi (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    severity numeric NOT NULL,
    improvement numeric NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE cgi OWNER TO jolo;

--
-- TOC entry 263 (class 1259 OID 17124)
-- Name: cgi_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE cgi_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE cgi_id_seq OWNER TO jolo;

--
-- TOC entry 2673 (class 0 OID 0)
-- Dependencies: 263
-- Name: cgi_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE cgi_id_seq OWNED BY cgi.id;


--
-- TOC entry 178 (class 1259 OID 16420)
-- Name: channel_into_patient; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE channel_into_patient (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT channel_into_patient_name_check CHECK ((length(name) > 1))
);


ALTER TABLE channel_into_patient OWNER TO jolo;

--
-- TOC entry 179 (class 1259 OID 16428)
-- Name: channel_into_patient_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE channel_into_patient_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE channel_into_patient_id_seq OWNER TO jolo;

--
-- TOC entry 2674 (class 0 OID 0)
-- Dependencies: 179
-- Name: channel_into_patient_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE channel_into_patient_id_seq OWNED BY channel_into_patient.id;


--
-- TOC entry 258 (class 1259 OID 17027)
-- Name: collateral_effect; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE collateral_effect (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE collateral_effect OWNER TO jolo;

--
-- TOC entry 257 (class 1259 OID 17025)
-- Name: collateral_effect_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE collateral_effect_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE collateral_effect_id_seq OWNER TO jolo;

--
-- TOC entry 2675 (class 0 OID 0)
-- Dependencies: 257
-- Name: collateral_effect_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE collateral_effect_id_seq OWNED BY collateral_effect.id;


--
-- TOC entry 180 (class 1259 OID 16430)
-- Name: seq_prescriptions; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE seq_prescriptions
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE seq_prescriptions OWNER TO jolo;

--
-- TOC entry 181 (class 1259 OID 16432)
-- Name: depot_prescription; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE depot_prescription (
    id integer DEFAULT nextval('seq_prescriptions'::regclass) NOT NULL,
    survey_id integer NOT NULL,
    prescribeable_drug_id integer NOT NULL,
    last_injection_on date,
    dosage numeric(10,4) NOT NULL,
    injection_interval_in_days integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT depot_prescription_dosage_check CHECK ((dosage >= 0.0)),
    CONSTRAINT depot_prescription_injection_interval_in_days_check CHECK ((injection_interval_in_days > 0)),
    CONSTRAINT depot_prescription_last_injection_on_check CHECK ((last_injection_on <= ('now'::text)::date))
);


ALTER TABLE depot_prescription OWNER TO jolo;

--
-- TOC entry 182 (class 1259 OID 16443)
-- Name: drug; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE drug (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT drug_name_check CHECK ((length(name) > 1))
);


ALTER TABLE drug OWNER TO jolo;

--
-- TOC entry 183 (class 1259 OID 16451)
-- Name: drug_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE drug_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE drug_id_seq OWNER TO jolo;

--
-- TOC entry 2676 (class 0 OID 0)
-- Dependencies: 183
-- Name: drug_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE drug_id_seq OWNED BY drug.id;


--
-- TOC entry 268 (class 1259 OID 17164)
-- Name: fps; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE fps (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    fps_value numeric NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE fps OWNER TO jolo;

--
-- TOC entry 267 (class 1259 OID 17162)
-- Name: fps_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE fps_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE fps_id_seq OWNER TO jolo;

--
-- TOC entry 2677 (class 0 OID 0)
-- Dependencies: 267
-- Name: fps_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE fps_id_seq OWNED BY fps.id;


--
-- TOC entry 266 (class 1259 OID 17145)
-- Name: gaf; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE gaf (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    gaf_value numeric NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE gaf OWNER TO jolo;

--
-- TOC entry 265 (class 1259 OID 17143)
-- Name: gaf_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE gaf_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE gaf_id_seq OWNER TO jolo;

--
-- TOC entry 2678 (class 0 OID 0)
-- Dependencies: 265
-- Name: gaf_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE gaf_id_seq OWNED BY gaf.id;


--
-- TOC entry 252 (class 1259 OID 16984)
-- Name: icd10_diagnosis; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE icd10_diagnosis (
    id integer NOT NULL,
    name text NOT NULL,
    long_name text DEFAULT ''::text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE icd10_diagnosis OWNER TO jolo;

--
-- TOC entry 251 (class 1259 OID 16982)
-- Name: icd10_diagnosis_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE icd10_diagnosis_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE icd10_diagnosis_id_seq OWNER TO jolo;

--
-- TOC entry 2679 (class 0 OID 0)
-- Dependencies: 251
-- Name: icd10_diagnosis_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE icd10_diagnosis_id_seq OWNED BY icd10_diagnosis.id;


--
-- TOC entry 259 (class 1259 OID 17044)
-- Name: icd10_survey; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE icd10_survey (
    icd10_diagnosis_id integer NOT NULL,
    survey_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    id integer NOT NULL
);


ALTER TABLE icd10_survey OWNER TO jolo;

--
-- TOC entry 260 (class 1259 OID 17063)
-- Name: icd10_survey_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE icd10_survey_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE icd10_survey_id_seq OWNER TO jolo;

--
-- TOC entry 2680 (class 0 OID 0)
-- Dependencies: 260
-- Name: icd10_survey_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE icd10_survey_id_seq OWNED BY icd10_survey.id;


--
-- TOC entry 184 (class 1259 OID 16453)
-- Name: molecule; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE molecule (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    molecule_class_id integer NOT NULL,
    CONSTRAINT molecule_name_check CHECK ((length(name) > 1))
);


ALTER TABLE molecule OWNER TO jolo;

--
-- TOC entry 185 (class 1259 OID 16461)
-- Name: molecule_class; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE molecule_class (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT molecule_class_name_check CHECK ((length(name) > 1))
);


ALTER TABLE molecule_class OWNER TO jolo;

--
-- TOC entry 186 (class 1259 OID 16469)
-- Name: molecule_class_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE molecule_class_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE molecule_class_id_seq OWNER TO jolo;

--
-- TOC entry 2681 (class 0 OID 0)
-- Dependencies: 186
-- Name: molecule_class_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE molecule_class_id_seq OWNED BY molecule_class.id;


--
-- TOC entry 187 (class 1259 OID 16471)
-- Name: molecule_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE molecule_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE molecule_id_seq OWNER TO jolo;

--
-- TOC entry 2682 (class 0 OID 0)
-- Dependencies: 187
-- Name: molecule_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE molecule_id_seq OWNED BY molecule.id;


--
-- TOC entry 188 (class 1259 OID 16473)
-- Name: optional_prescription; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE optional_prescription (
    id integer DEFAULT nextval('seq_prescriptions'::regclass) NOT NULL,
    survey_id integer NOT NULL,
    drug_id integer,
    comment text DEFAULT ''::text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE optional_prescription OWNER TO jolo;

--
-- TOC entry 250 (class 1259 OID 16970)
-- Name: organization_unit; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE organization_unit (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE organization_unit OWNER TO jolo;

--
-- TOC entry 249 (class 1259 OID 16968)
-- Name: organization_unit_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE organization_unit_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE organization_unit_id_seq OWNER TO jolo;

--
-- TOC entry 2683 (class 0 OID 0)
-- Dependencies: 249
-- Name: organization_unit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE organization_unit_id_seq OWNED BY organization_unit.id;


--
-- TOC entry 189 (class 1259 OID 16481)
-- Name: plasmatic_level; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE plasmatic_level (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    molecule_id integer NOT NULL,
    concentration_value numeric(10,4),
    unit_id integer,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE plasmatic_level OWNER TO jolo;

--
-- TOC entry 190 (class 1259 OID 16488)
-- Name: plasmatic_level_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE plasmatic_level_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE plasmatic_level_id_seq OWNER TO jolo;

--
-- TOC entry 2684 (class 0 OID 0)
-- Dependencies: 190
-- Name: plasmatic_level_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE plasmatic_level_id_seq OWNED BY plasmatic_level.id;


--
-- TOC entry 191 (class 1259 OID 16490)
-- Name: prescribeable_drug; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE prescribeable_drug (
    id integer NOT NULL,
    drug_id integer NOT NULL,
    name text NOT NULL,
    dosage numeric(10,2) NOT NULL,
    dosage_unit_id integer NOT NULL,
    administration_method_id integer NOT NULL,
    CONSTRAINT prescribeable_drug_dosage_check CHECK ((dosage > 0.0)),
    CONSTRAINT prescribeable_drug_name_check CHECK ((length(name) > 1))
);


ALTER TABLE prescribeable_drug OWNER TO jolo;

--
-- TOC entry 192 (class 1259 OID 16498)
-- Name: prescribeable_drug_composition; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE prescribeable_drug_composition (
    id integer NOT NULL,
    prescribeable_drug_id integer NOT NULL,
    molecule_id integer NOT NULL,
    amount numeric(10,2) NOT NULL,
    amount_unit_id integer NOT NULL,
    CONSTRAINT prescribeable_drug_composition_amount_check CHECK ((amount > 0.0))
);


ALTER TABLE prescribeable_drug_composition OWNER TO jolo;

--
-- TOC entry 193 (class 1259 OID 16502)
-- Name: prescribeable_drug_composition_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE prescribeable_drug_composition_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE prescribeable_drug_composition_id_seq OWNER TO jolo;

--
-- TOC entry 2685 (class 0 OID 0)
-- Dependencies: 193
-- Name: prescribeable_drug_composition_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE prescribeable_drug_composition_id_seq OWNED BY prescribeable_drug_composition.id;


--
-- TOC entry 194 (class 1259 OID 16504)
-- Name: prescribeable_drug_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE prescribeable_drug_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE prescribeable_drug_id_seq OWNER TO jolo;

--
-- TOC entry 2686 (class 0 OID 0)
-- Dependencies: 194
-- Name: prescribeable_drug_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE prescribeable_drug_id_seq OWNED BY prescribeable_drug.id;


--
-- TOC entry 195 (class 1259 OID 16506)
-- Name: proband; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE proband (
    id integer NOT NULL,
    external_id integer NOT NULL,
    birthday date NOT NULL,
    height_in_cm integer,
    sex_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    surname text DEFAULT ''::text NOT NULL,
    first_name text DEFAULT ''::text NOT NULL,
    CONSTRAINT proband_birthday_check CHECK ((birthday < ('now'::text)::date)),
    CONSTRAINT proband_height_in_cm_check CHECK (((height_in_cm >= 50) AND (height_in_cm <= 220)))
);


ALTER TABLE proband OWNER TO jolo;

--
-- TOC entry 196 (class 1259 OID 16515)
-- Name: proband_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE proband_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE proband_id_seq OWNER TO jolo;

--
-- TOC entry 2687 (class 0 OID 0)
-- Dependencies: 196
-- Name: proband_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE proband_id_seq OWNED BY proband.id;


--
-- TOC entry 197 (class 1259 OID 16517)
-- Name: project; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE project (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT project_name_check CHECK ((length(name) > 1))
);


ALTER TABLE project OWNER TO jolo;

--
-- TOC entry 198 (class 1259 OID 16525)
-- Name: project_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE project_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE project_id_seq OWNER TO jolo;

--
-- TOC entry 2688 (class 0 OID 0)
-- Dependencies: 198
-- Name: project_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE project_id_seq OWNED BY project.id;


--
-- TOC entry 199 (class 1259 OID 16527)
-- Name: regular_prescription; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE regular_prescription (
    id integer DEFAULT nextval('seq_prescriptions'::regclass) NOT NULL,
    survey_id integer NOT NULL,
    prescribeable_drug_id integer NOT NULL,
    morning_dosage numeric(10,2) DEFAULT 0.0 NOT NULL,
    lunch_dosage numeric(10,2) DEFAULT 0.0 NOT NULL,
    noon_dosage numeric(10,2) DEFAULT 0.0 NOT NULL,
    night_dosage numeric(10,2) DEFAULT 0.0 NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT regular_prescription_check CHECK (((((morning_dosage > 0.0) OR (lunch_dosage > 0.0)) OR (noon_dosage > 0.0)) OR (night_dosage > 0.0)))
);


ALTER TABLE regular_prescription OWNER TO jolo;

--
-- TOC entry 200 (class 1259 OID 16540)
-- Name: sex; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE sex (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT sex_name_check CHECK ((length(name) >= 1))
);


ALTER TABLE sex OWNER TO jolo;

--
-- TOC entry 201 (class 1259 OID 16548)
-- Name: sex_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE sex_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE sex_id_seq OWNER TO jolo;

--
-- TOC entry 2689 (class 0 OID 0)
-- Dependencies: 201
-- Name: sex_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE sex_id_seq OWNED BY sex.id;


--
-- TOC entry 256 (class 1259 OID 17013)
-- Name: smoking_habit; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE smoking_habit (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE smoking_habit OWNER TO jolo;

--
-- TOC entry 255 (class 1259 OID 17011)
-- Name: smoking_habit_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE smoking_habit_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE smoking_habit_id_seq OWNER TO jolo;

--
-- TOC entry 2690 (class 0 OID 0)
-- Dependencies: 255
-- Name: smoking_habit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE smoking_habit_id_seq OWNED BY smoking_habit.id;


--
-- TOC entry 202 (class 1259 OID 16550)
-- Name: survey; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE survey (
    id integer NOT NULL,
    proband_id integer NOT NULL,
    campaign_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    survey_date date NOT NULL,
    organization_unit_id integer DEFAULT 2 NOT NULL,
    smoking_habit_id integer DEFAULT 2 NOT NULL,
    bmi numeric DEFAULT 0.0 NOT NULL,
    CONSTRAINT survey_survey_date_check CHECK ((survey_date <= ('now'::text)::date))
);


ALTER TABLE survey OWNER TO jolo;

--
-- TOC entry 262 (class 1259 OID 17079)
-- Name: survey_collateral_effect; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE survey_collateral_effect (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    collateral_effect_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE survey_collateral_effect OWNER TO jolo;

--
-- TOC entry 261 (class 1259 OID 17077)
-- Name: survey_collateral_effect_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE survey_collateral_effect_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE survey_collateral_effect_id_seq OWNER TO jolo;

--
-- TOC entry 2691 (class 0 OID 0)
-- Dependencies: 261
-- Name: survey_collateral_effect_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_collateral_effect_id_seq OWNED BY survey_collateral_effect.id;


--
-- TOC entry 203 (class 1259 OID 16558)
-- Name: survey_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE survey_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE survey_id_seq OWNER TO jolo;

--
-- TOC entry 2692 (class 0 OID 0)
-- Dependencies: 203
-- Name: survey_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_id_seq OWNED BY survey.id;


--
-- TOC entry 204 (class 1259 OID 16560)
-- Name: survey_info; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE survey_info (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    weight_in_kg numeric(10,2),
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE survey_info OWNER TO jolo;

--
-- TOC entry 2693 (class 0 OID 0)
-- Dependencies: 204
-- Name: TABLE survey_info; Type: COMMENT; Schema: core; Owner: jolo
--

COMMENT ON TABLE survey_info IS 'add additional uncathegorized info to this table!';


--
-- TOC entry 205 (class 1259 OID 16567)
-- Name: survey_info_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE survey_info_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE survey_info_id_seq OWNER TO jolo;

--
-- TOC entry 2694 (class 0 OID 0)
-- Dependencies: 205
-- Name: survey_info_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_info_id_seq OWNED BY survey_info.id;


--
-- TOC entry 206 (class 1259 OID 16569)
-- Name: unit; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE unit (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT unit_name_check CHECK ((length(name) > 1))
);


ALTER TABLE unit OWNER TO jolo;

--
-- TOC entry 207 (class 1259 OID 16577)
-- Name: unit_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE unit_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE unit_id_seq OWNER TO jolo;

--
-- TOC entry 2695 (class 0 OID 0)
-- Dependencies: 207
-- Name: unit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE unit_id_seq OWNED BY unit.id;


--
-- TOC entry 270 (class 1259 OID 17183)
-- Name: who_qol; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE who_qol (
    id integer NOT NULL,
    survey_id integer NOT NULL,
    physical numeric NOT NULL,
    psychological numeric NOT NULL,
    social numeric NOT NULL,
    environmental numeric NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE who_qol OWNER TO jolo;

--
-- TOC entry 269 (class 1259 OID 17181)
-- Name: who_qol_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE who_qol_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE who_qol_id_seq OWNER TO jolo;

--
-- TOC entry 2696 (class 0 OID 0)
-- Dependencies: 269
-- Name: who_qol_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE who_qol_id_seq OWNED BY who_qol.id;


SET search_path = stat, pg_catalog;

--
-- TOC entry 208 (class 1259 OID 16579)
-- Name: alter_zum_referenzdatum; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW alter_zum_referenzdatum AS
 SELECT pr.name AS project_name,
    c.name AS campaign_name,
    p.id AS proband_id,
    sx.name AS sex_name,
    (date_part('year'::text, s.survey_date) - date_part('year'::text, p.birthday)) AS age
   FROM ((((core.project pr
     JOIN core.campaign c ON ((pr.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
     JOIN core.sex sx ON ((p.sex_id = sx.id)));


ALTER TABLE alter_zum_referenzdatum OWNER TO jolo;

--
-- TOC entry 209 (class 1259 OID 16584)
-- Name: altersverteilung; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW altersverteilung AS
 SELECT min(alter_zum_referenzdatum.age) AS minimum,
    max(alter_zum_referenzdatum.age) AS maximum,
    round(avg(alter_zum_referenzdatum.age)) AS durchschnitt
   FROM alter_zum_referenzdatum;


ALTER TABLE altersverteilung OWNER TO jolo;

--
-- TOC entry 210 (class 1259 OID 16588)
-- Name: altersverteilung_nach_geschlecht; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW altersverteilung_nach_geschlecht AS
 SELECT alter_zum_referenzdatum.sex_name,
    min(alter_zum_referenzdatum.age) AS minimum,
    max(alter_zum_referenzdatum.age) AS maximum,
    round(avg(alter_zum_referenzdatum.age)) AS durchschnitt
   FROM alter_zum_referenzdatum
  GROUP BY alter_zum_referenzdatum.sex_name;


ALTER TABLE altersverteilung_nach_geschlecht OWNER TO jolo;

--
-- TOC entry 211 (class 1259 OID 16592)
-- Name: anzahl_atypische_antipsychotika_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_atypische_antipsychotika_pro_patient AS
 SELECT sq.cnt AS anzahl_atypische_antipsychotika,
    count(1) AS anzahl_faelle
   FROM ( SELECT prob.id AS proband_id,
            count(1) AS cnt
           FROM ((((((core.proband prob
             JOIN core.survey s ON ((s.proband_id = prob.id)))
             JOIN core.regular_prescription rp ON ((s.id = rp.survey_id)))
             JOIN core.prescribeable_drug pd ON ((rp.prescribeable_drug_id = pd.id)))
             JOIN core.prescribeable_drug_composition pdc ON ((pd.id = pdc.prescribeable_drug_id)))
             JOIN core.molecule m ON ((pdc.molecule_id = m.id)))
             JOIN core.molecule_class mc ON ((m.molecule_class_id = mc.id)))
          WHERE (mc.name = 'Atypische Antipsychotika'::text)
          GROUP BY prob.id
          ORDER BY count(1) DESC) sq
  GROUP BY sq.cnt
  ORDER BY sq.cnt DESC;


ALTER TABLE anzahl_atypische_antipsychotika_pro_patient OWNER TO jolo;

--
-- TOC entry 212 (class 1259 OID 16597)
-- Name: anzahl_depotverordnungen_pro_project; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_depotverordnungen_pro_project AS
 SELECT proj.name AS project_name,
    count(1) AS anzahl_depotverordnungen
   FROM ((((core.depot_prescription p
     JOIN core.survey s ON ((p.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.proband prob ON ((s.proband_id = prob.id)))
  GROUP BY proj.name;


ALTER TABLE anzahl_depotverordnungen_pro_project OWNER TO jolo;

--
-- TOC entry 213 (class 1259 OID 16602)
-- Name: anzahl_depotverschreibungen_pro_projekt; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_depotverschreibungen_pro_projekt AS
 SELECT count(1) AS anzahl_verschreibungen,
    m.name AS wirkstoff,
    proj.name AS projekt
   FROM (((((((core.molecule m
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.depot_prescription dp ON ((pd.id = dp.prescribeable_drug_id)))
     JOIN core.survey s ON ((dp.survey_id = s.id)))
     JOIN core.proband prob ON ((s.proband_id = prob.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
  GROUP BY proj.name, m.name
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_depotverschreibungen_pro_projekt OWNER TO jolo;

--
-- TOC entry 214 (class 1259 OID 16607)
-- Name: anzahl_wirkstoffklassen_in_tagesmedikation_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_wirkstoffklassen_in_tagesmedikation_pro_patient AS
 SELECT count(1) AS anzahl_verschreibungen,
    proj.name AS project_name,
    mc.name AS wirkstoffklasse
   FROM ((((((((core.molecule m
     JOIN core.prescribeable_drug_composition dc ON ((m.id = dc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((dc.prescribeable_drug_id = pd.id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
     JOIN core.molecule_class mc ON ((m.molecule_class_id = mc.id)))
  GROUP BY proj.name, s.proband_id, mc.name
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_wirkstoffklassen_in_tagesmedikation_pro_patient OWNER TO jolo;

--
-- TOC entry 215 (class 1259 OID 16612)
-- Name: anzahl_faelle_mit_wirkstoffklassenverordnungen_pro_proband; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_faelle_mit_wirkstoffklassenverordnungen_pro_proband AS
 SELECT count(1) AS anzahl_faelle,
    s.wirkstoffklasse
   FROM anzahl_wirkstoffklassen_in_tagesmedikation_pro_patient s
  GROUP BY s.wirkstoffklasse
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_faelle_mit_wirkstoffklassenverordnungen_pro_proband OWNER TO jolo;

--
-- TOC entry 216 (class 1259 OID 16616)
-- Name: anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient AS
 SELECT count(1) AS anzahl_antipsychotische_wirkstoffklassen,
    mc.name AS wirkstoffklasse,
    p.name AS project_name,
    c.name AS campaign_name
   FROM ((((((((core.molecule_class mc
     JOIN core.molecule m ON ((m.molecule_class_id = mc.id)))
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pd.id = pdc.prescribeable_drug_id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project p ON ((c.project_id = p.id)))
     JOIN core.proband prob ON ((s.proband_id = prob.id)))
  WHERE ((mc.name = 'Typische Antipsychotika'::text) OR (mc.name = 'Atypische Antipsychotika'::text))
  GROUP BY prob.id, mc.name, c.name, p.name
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient OWNER TO jolo;

--
-- TOC entry 217 (class 1259 OID 16621)
-- Name: anzahl_faelle_verordnete_antipsychitische_wirkstoffklassen_pro_; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_faelle_verordnete_antipsychitische_wirkstoffklassen_pro_ AS
 SELECT anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient.anzahl_antipsychotische_wirkstoffklassen,
    count(1) AS anzahl_faelle,
    anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient.project_name
   FROM anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient
  GROUP BY anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient.anzahl_antipsychotische_wirkstoffklassen, anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient.project_name
  ORDER BY anzahl_verordnete_antipsychotische_wirkstoffklassen_pro_patient.anzahl_antipsychotische_wirkstoffklassen DESC;


ALTER TABLE anzahl_faelle_verordnete_antipsychitische_wirkstoffklassen_pro_ OWNER TO jolo;

--
-- TOC entry 218 (class 1259 OID 16625)
-- Name: anzahl_maenner_frauen_pro_kampagne; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_maenner_frauen_pro_kampagne AS
 SELECT proj.name AS projekt_name,
    c.name AS kampagne,
    sx.name AS geschlecht,
    count(1) AS anzahl
   FROM ((((core.project proj
     JOIN core.campaign c ON ((c.project_id = proj.id)))
     JOIN core.survey s ON ((s.campaign_id = c.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
     JOIN core.sex sx ON ((p.sex_id = sx.id)))
  GROUP BY proj.name, c.name, sx.name
  ORDER BY proj.name, c.name, sx.name;


ALTER TABLE anzahl_maenner_frauen_pro_kampagne OWNER TO jolo;

--
-- TOC entry 219 (class 1259 OID 16630)
-- Name: anzahl_maenner_frauen_pro_projekt; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_maenner_frauen_pro_projekt AS
 SELECT proj.name AS projekt_name,
    sx.name AS geschlecht,
    count(1) AS anzahl
   FROM ((((core.project proj
     JOIN core.campaign c ON ((c.project_id = proj.id)))
     JOIN core.survey s ON ((s.campaign_id = c.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
     JOIN core.sex sx ON ((p.sex_id = sx.id)))
  GROUP BY proj.name, sx.name
  ORDER BY proj.name, sx.name;


ALTER TABLE anzahl_maenner_frauen_pro_projekt OWNER TO jolo;

--
-- TOC entry 220 (class 1259 OID 16635)
-- Name: anzahl_patienten_mit_plasmaspiegel; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_patienten_mit_plasmaspiegel AS
 SELECT count(1) AS anzahl_patienten_mit_plasmaspiegel
   FROM ( SELECT prob.id
           FROM ((core.plasmatic_level pl
             JOIN core.survey s ON ((pl.survey_id = s.id)))
             JOIN core.proband prob ON ((s.proband_id = prob.id)))
          GROUP BY prob.id) sq;


ALTER TABLE anzahl_patienten_mit_plasmaspiegel OWNER TO jolo;

--
-- TOC entry 221 (class 1259 OID 16640)
-- Name: anzahl_plasmaspiegel_pro_proband; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_plasmaspiegel_pro_proband AS
 SELECT prob.id AS proband_id,
    count(1) AS anzahl_probanden_mit_plasmaspiegel
   FROM ((((core.proband prob
     JOIN core.survey s ON ((prob.id = s.proband_id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.plasmatic_level pl ON ((s.id = pl.survey_id)))
  GROUP BY prob.id
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_plasmaspiegel_pro_proband OWNER TO jolo;

--
-- TOC entry 222 (class 1259 OID 16645)
-- Name: anzahl_plasmaspiegel_pro_project; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_plasmaspiegel_pro_project AS
 SELECT proj.name AS project_name,
    count(1) AS anzahl_plasmaspiegel
   FROM ((((core.proband prob
     JOIN core.survey s ON ((prob.id = s.proband_id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.plasmatic_level pl ON ((s.id = pl.survey_id)))
  GROUP BY proj.name;


ALTER TABLE anzahl_plasmaspiegel_pro_project OWNER TO jolo;

--
-- TOC entry 223 (class 1259 OID 16650)
-- Name: anzahl_plasmaspiegel_pro_wirkstoff; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_plasmaspiegel_pro_wirkstoff AS
 SELECT m.name AS wirkstoff,
    count(1) AS anzahl_plasmaspiegel
   FROM (((((core.proband prob
     JOIN core.survey s ON ((prob.id = s.proband_id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.plasmatic_level pl ON ((s.id = pl.survey_id)))
     JOIN core.molecule m ON ((pl.molecule_id = m.id)))
  GROUP BY m.name
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_plasmaspiegel_pro_wirkstoff OWNER TO jolo;

--
-- TOC entry 224 (class 1259 OID 16655)
-- Name: anzahl_probanden_pro_kampagne; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_probanden_pro_kampagne AS
 SELECT proj.name AS projekt,
    c.name AS kampagne,
    count(1) AS anzahl_probanden
   FROM (((core.project proj
     JOIN core.campaign c ON ((c.project_id = proj.id)))
     JOIN core.survey s ON ((s.campaign_id = c.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
  GROUP BY proj.name, c.name
  ORDER BY proj.name, c.name;


ALTER TABLE anzahl_probanden_pro_kampagne OWNER TO jolo;

--
-- TOC entry 225 (class 1259 OID 16660)
-- Name: anzahl_probanden_pro_projekt; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_probanden_pro_projekt AS
 SELECT proj.name AS project_name,
    count(1) AS anzahl_probanden
   FROM (((core.project proj
     JOIN core.campaign c ON ((c.project_id = proj.id)))
     JOIN core.survey s ON ((s.campaign_id = c.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
  GROUP BY proj.name;


ALTER TABLE anzahl_probanden_pro_projekt OWNER TO jolo;

--
-- TOC entry 226 (class 1259 OID 16665)
-- Name: anzahl_typische_antipsychotika_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_typische_antipsychotika_pro_patient AS
 SELECT sq.cnt AS anzahl_atypische_antipsychotika,
    count(1) AS anzahl_faelle
   FROM ( SELECT prob.id AS proband_id,
            count(1) AS cnt
           FROM ((((((core.proband prob
             JOIN core.survey s ON ((s.proband_id = prob.id)))
             JOIN core.regular_prescription rp ON ((s.id = rp.survey_id)))
             JOIN core.prescribeable_drug pd ON ((rp.prescribeable_drug_id = pd.id)))
             JOIN core.prescribeable_drug_composition pdc ON ((pd.id = pdc.prescribeable_drug_id)))
             JOIN core.molecule m ON ((pdc.molecule_id = m.id)))
             JOIN core.molecule_class mc ON ((m.molecule_class_id = mc.id)))
          WHERE (mc.name = 'Typische Antipsychotika'::text)
          GROUP BY prob.id
          ORDER BY count(1) DESC) sq
  GROUP BY sq.cnt
  ORDER BY sq.cnt DESC;


ALTER TABLE anzahl_typische_antipsychotika_pro_patient OWNER TO jolo;

--
-- TOC entry 227 (class 1259 OID 16670)
-- Name: anzahl_verschreibungen_in_depotmed_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_verschreibungen_in_depotmed_pro_patient AS
 SELECT p.name AS project_name,
    m.name AS wirkstoff,
    count(1) AS anzahl_verordnungen
   FROM (((((((core.molecule m
     JOIN core.prescribeable_drug_composition pdc ON ((pdc.molecule_id = m.id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.depot_prescription dp ON ((pd.id = dp.prescribeable_drug_id)))
     JOIN core.survey s ON ((dp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project p ON ((c.project_id = p.id)))
     JOIN core.proband prob ON ((s.proband_id = prob.id)))
  GROUP BY p.name, m.name
  ORDER BY count(1) DESC, m.name;


ALTER TABLE anzahl_verschreibungen_in_depotmed_pro_patient OWNER TO jolo;

--
-- TOC entry 228 (class 1259 OID 16675)
-- Name: anzahl_verschreibungen_in_tagesmed_pro_patient; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_verschreibungen_in_tagesmed_pro_patient AS
 SELECT count(1) AS anzahl_verschreibungen,
    proj.name AS project_name,
    c.name AS campaign_name
   FROM (((((((core.molecule m
     JOIN core.prescribeable_drug_composition dc ON ((m.id = dc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((dc.prescribeable_drug_id = pd.id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
  GROUP BY proj.name, c.name, s.proband_id
  ORDER BY count(1) DESC;


ALTER TABLE anzahl_verschreibungen_in_tagesmed_pro_patient OWNER TO jolo;

--
-- TOC entry 229 (class 1259 OID 16680)
-- Name: anzahl_verschreibungen_tagesmed_anzahl_faelle; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW anzahl_verschreibungen_tagesmed_anzahl_faelle AS
 SELECT anzahl_verschreibungen_in_tagesmed_pro_patient.anzahl_verschreibungen,
    count(1) AS anzahl_faelle
   FROM anzahl_verschreibungen_in_tagesmed_pro_patient
  GROUP BY anzahl_verschreibungen_in_tagesmed_pro_patient.anzahl_verschreibungen
  ORDER BY anzahl_verschreibungen_in_tagesmed_pro_patient.anzahl_verschreibungen DESC;


ALTER TABLE anzahl_verschreibungen_tagesmed_anzahl_faelle OWNER TO jolo;

--
-- TOC entry 230 (class 1259 OID 16684)
-- Name: depotdosierungen; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW depotdosierungen AS
 SELECT mc.name AS wirkstoffklasse,
    m.name AS wirkstoff,
    (pd.dosage * dp.dosage) AS wirkstoffdosis,
    mu.name AS masseinheit,
    proj.name AS projekt,
    c.name AS kampagne
   FROM ((((((((core.molecule_class mc
     JOIN core.molecule m ON ((mc.id = m.molecule_class_id)))
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.depot_prescription dp ON ((pd.id = dp.prescribeable_drug_id)))
     JOIN core.survey s ON ((dp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.unit mu ON ((pdc.amount_unit_id = mu.id)))
  ORDER BY mc.name, m.name, (pd.dosage * dp.dosage);


ALTER TABLE depotdosierungen OWNER TO jolo;

--
-- TOC entry 231 (class 1259 OID 16689)
-- Name: depotverschreibungen_pro_projekt; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW depotverschreibungen_pro_projekt AS
 SELECT p.name AS project_name,
    pd.name AS prescribed_drug,
    pd.dosage AS dosis
   FROM ((((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.depot_prescription dp ON ((s.id = dp.survey_id)))
     JOIN core.prescribeable_drug pd ON ((dp.prescribeable_drug_id = pd.id)));


ALTER TABLE depotverschreibungen_pro_projekt OWNER TO jolo;

--
-- TOC entry 232 (class 1259 OID 16694)
-- Name: faelle_mit_anzahl_wirkstoffverordnungen_pro_proband; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW faelle_mit_anzahl_wirkstoffverordnungen_pro_proband AS
 SELECT count(1) AS anzahl_faelle,
    anzahl_verschreibungen_in_tagesmed_pro_patient.anzahl_verschreibungen,
    anzahl_verschreibungen_in_tagesmed_pro_patient.project_name
   FROM anzahl_verschreibungen_in_tagesmed_pro_patient
  GROUP BY anzahl_verschreibungen_in_tagesmed_pro_patient.project_name, anzahl_verschreibungen_in_tagesmed_pro_patient.anzahl_verschreibungen
  ORDER BY count(1) DESC;


ALTER TABLE faelle_mit_anzahl_wirkstoffverordnungen_pro_proband OWNER TO jolo;

--
-- TOC entry 233 (class 1259 OID 16698)
-- Name: geschlechterverteilung; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW geschlechterverteilung AS
 SELECT pr.name AS project_name,
    c.name AS campaign_name,
    sx.name AS sex_name,
    count(pr.id) AS anzahl
   FROM ((((core.proband p
     JOIN core.survey s ON ((p.id = s.proband_id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project pr ON ((c.project_id = pr.id)))
     JOIN core.sex sx ON ((p.sex_id = sx.id)))
  GROUP BY pr.name, c.name, sx.name
  ORDER BY pr.name, c.name, sx.name, count(pr.id);


ALTER TABLE geschlechterverteilung OWNER TO jolo;

--
-- TOC entry 234 (class 1259 OID 16703)
-- Name: hitliste_antipsychotika; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW hitliste_antipsychotika AS
 SELECT m.name AS molecule,
    count(1) AS anzahl_verordnungen
   FROM ((((core.molecule_class mc
     JOIN core.molecule m ON ((mc.id = m.molecule_class_id)))
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
  WHERE ((mc.name = 'Typische Antipsychotika'::text) OR (mc.name = 'Atypische Antipsychotika'::text))
  GROUP BY m.name
  ORDER BY count(1) DESC, m.name;


ALTER TABLE hitliste_antipsychotika OWNER TO jolo;

--
-- TOC entry 235 (class 1259 OID 16708)
-- Name: hitliste_wirkstoffe_in_plasmaspiegel; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW hitliste_wirkstoffe_in_plasmaspiegel AS
 SELECT count(1) AS cnt,
    m.name AS molecule_name
   FROM (core.plasmatic_level pl
     JOIN core.molecule m ON ((pl.molecule_id = m.id)))
  GROUP BY m.name
  ORDER BY count(1) DESC, m.name;


ALTER TABLE hitliste_wirkstoffe_in_plasmaspiegel OWNER TO jolo;

--
-- TOC entry 236 (class 1259 OID 16712)
-- Name: patienten_ohne_tagesmedikation_pro_project; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW patienten_ohne_tagesmedikation_pro_project AS
 SELECT p.name AS project_name,
    count(1) AS anzahl_probanden_ohne_tagesmedikation_pro_project
   FROM (((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.proband pr ON ((s.proband_id = pr.id)))
  WHERE (NOT (pr.id IN ( SELECT DISTINCT prbnd.id
           FROM ((core.regular_prescription rp
             JOIN core.survey srv ON ((rp.survey_id = srv.id)))
             JOIN core.proband prbnd ON ((srv.proband_id = prbnd.id))))))
  GROUP BY p.name;


ALTER TABLE patienten_ohne_tagesmedikation_pro_project OWNER TO jolo;

--
-- TOC entry 237 (class 1259 OID 16717)
-- Name: probanden_pro_kampagne; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probanden_pro_kampagne AS
 SELECT pr.name AS project,
    c.name AS campaign,
    count(p.id) AS anzahl
   FROM (((core.campaign c
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.proband p ON ((s.proband_id = p.id)))
     JOIN core.project pr ON ((pr.id = c.project_id)))
  GROUP BY c.name, pr.name
  ORDER BY count(p.id) DESC;


ALTER TABLE probanden_pro_kampagne OWNER TO jolo;

--
-- TOC entry 238 (class 1259 OID 16722)
-- Name: probandenalter_ip_2012; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probandenalter_ip_2012 AS
 SELECT alter_zum_referenzdatum.campaign_name AS kampagne,
    alter_zum_referenzdatum.age
   FROM alter_zum_referenzdatum
  WHERE (alter_zum_referenzdatum.campaign_name = 'Interventi Precoci 2012'::text)
  ORDER BY alter_zum_referenzdatum.campaign_name, alter_zum_referenzdatum.age;


ALTER TABLE probandenalter_ip_2012 OWNER TO jolo;

--
-- TOC entry 239 (class 1259 OID 16726)
-- Name: probandenalter_ip_2013; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probandenalter_ip_2013 AS
 SELECT alter_zum_referenzdatum.campaign_name AS kampagne,
    alter_zum_referenzdatum.age
   FROM alter_zum_referenzdatum
  WHERE (alter_zum_referenzdatum.campaign_name = 'Interventi Precoci 2013'::text)
  ORDER BY alter_zum_referenzdatum.campaign_name, alter_zum_referenzdatum.age;


ALTER TABLE probandenalter_ip_2013 OWNER TO jolo;

--
-- TOC entry 240 (class 1259 OID 16730)
-- Name: probandenalter_ip_2014; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probandenalter_ip_2014 AS
 SELECT alter_zum_referenzdatum.campaign_name AS kampagne,
    alter_zum_referenzdatum.age
   FROM alter_zum_referenzdatum
  WHERE (alter_zum_referenzdatum.campaign_name = 'Interventi Precoci 2014'::text)
  ORDER BY alter_zum_referenzdatum.campaign_name, alter_zum_referenzdatum.age;


ALTER TABLE probandenalter_ip_2014 OWNER TO jolo;

--
-- TOC entry 241 (class 1259 OID 16734)
-- Name: probandenalter_und_kampagne; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probandenalter_und_kampagne AS
 SELECT alter_zum_referenzdatum.campaign_name AS kampagne,
    alter_zum_referenzdatum.age
   FROM alter_zum_referenzdatum
  ORDER BY alter_zum_referenzdatum.campaign_name, alter_zum_referenzdatum.age;


ALTER TABLE probandenalter_und_kampagne OWNER TO jolo;

--
-- TOC entry 242 (class 1259 OID 16738)
-- Name: regular_medication_overview; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW regular_medication_overview AS
 SELECT p.id AS proband_id,
    pd.name AS prescribeable_drug_name,
    rp.morning_dosage,
    rp.lunch_dosage,
    rp.noon_dosage,
    rp.night_dosage
   FROM (((core.proband p
     JOIN core.survey s ON ((p.id = s.proband_id)))
     JOIN core.regular_prescription rp ON ((s.id = rp.survey_id)))
     JOIN core.prescribeable_drug pd ON ((pd.id = rp.prescribeable_drug_id)));


ALTER TABLE regular_medication_overview OWNER TO jolo;

--
-- TOC entry 243 (class 1259 OID 16743)
-- Name: regulare_prescription_molecule_amount_by_prescription; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW regulare_prescription_molecule_amount_by_prescription AS
 SELECT mc.name AS molecule_class,
    m.name AS molecule,
    pdc.amount AS molecule_amount_in_prescribeable_drug,
    (((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage) AS daily_dosage,
    u.name AS unit,
        CASE
            WHEN (am.name = 'Trpf'::text) THEN ((pdc.amount * (((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage)) / (20)::numeric)
            ELSE ((((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage) * pdc.amount)
        END AS daily_dosage_in_mg,
    am.name AS admin_method,
    prob.id AS proband_id
   FROM ((((((((core.regular_prescription rp
     JOIN core.prescribeable_drug pd ON ((rp.prescribeable_drug_id = pd.id)))
     JOIN core.prescribeable_drug_composition pdc ON ((pd.id = pdc.prescribeable_drug_id)))
     JOIN core.molecule m ON ((pdc.molecule_id = m.id)))
     JOIN core.administration_method am ON ((pd.administration_method_id = am.id)))
     JOIN core.unit u ON ((pdc.amount_unit_id = u.id)))
     JOIN core.molecule_class mc ON ((mc.id = m.molecule_class_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.proband prob ON ((prob.id = s.proband_id)))
  ORDER BY mc.name, m.name,
        CASE
            WHEN (am.name = 'Trpf'::text) THEN ((pdc.amount * (((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage)) / (20)::numeric)
            ELSE ((((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage) * pdc.amount)
        END;


ALTER TABLE regulare_prescription_molecule_amount_by_prescription OWNER TO jolo;

--
-- TOC entry 244 (class 1259 OID 16748)
-- Name: regular_prescription_daily_molecule_intake; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW regular_prescription_daily_molecule_intake AS
 SELECT regulare_prescription_molecule_amount_by_prescription.molecule,
    sum(regulare_prescription_molecule_amount_by_prescription.daily_dosage_in_mg) AS daily_intake_in_mg
   FROM regulare_prescription_molecule_amount_by_prescription
  GROUP BY regulare_prescription_molecule_amount_by_prescription.proband_id, regulare_prescription_molecule_amount_by_prescription.molecule
  ORDER BY regulare_prescription_molecule_amount_by_prescription.molecule, sum(regulare_prescription_molecule_amount_by_prescription.daily_dosage_in_mg) DESC;


ALTER TABLE regular_prescription_daily_molecule_intake OWNER TO jolo;

--
-- TOC entry 245 (class 1259 OID 16752)
-- Name: regular_prescription_molecule_intake_statistics; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW regular_prescription_molecule_intake_statistics AS
 SELECT regular_prescription_daily_molecule_intake.molecule,
    min(regular_prescription_daily_molecule_intake.daily_intake_in_mg) AS min_prescribed_dosage,
    max(regular_prescription_daily_molecule_intake.daily_intake_in_mg) AS max_prescribed_dosage,
    avg(regular_prescription_daily_molecule_intake.daily_intake_in_mg) AS avg_prescribed_dosage,
    exp(avg(
        CASE
            WHEN (regular_prescription_daily_molecule_intake.daily_intake_in_mg > 0.0) THEN ln(regular_prescription_daily_molecule_intake.daily_intake_in_mg)
            ELSE NULL::numeric
        END)) AS geom_mean_prescribed_dosage,
    count(1) AS number_of_probands
   FROM regular_prescription_daily_molecule_intake
  GROUP BY regular_prescription_daily_molecule_intake.molecule
  ORDER BY count(1) DESC;


ALTER TABLE regular_prescription_molecule_intake_statistics OWNER TO jolo;

--
-- TOC entry 246 (class 1259 OID 16756)
-- Name: tagesdosierung; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW tagesdosierung AS
 SELECT mc.name AS wirkstoffklasse,
    m.name AS wirkstoff,
    (pd.dosage * rp.morning_dosage) AS morgendosis,
    (pd.dosage * rp.lunch_dosage) AS mittagsdosis,
    (pd.dosage * rp.noon_dosage) AS abenddosis,
    (pd.dosage * rp.night_dosage) AS nachtdosis,
    (pd.dosage * (((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage)) AS tagesdosis,
    mu.name AS masseinheit,
    proj.name AS projekt,
    c.name AS kampagne,
    s.id AS survey_id
   FROM ((((((((core.molecule_class mc
     JOIN core.molecule m ON ((mc.id = m.molecule_class_id)))
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project proj ON ((c.project_id = proj.id)))
     JOIN core.unit mu ON ((pd.dosage_unit_id = mu.id)))
  ORDER BY mc.name, m.name, (pd.dosage * (((rp.morning_dosage + rp.lunch_dosage) + rp.noon_dosage) + rp.night_dosage));


ALTER TABLE tagesdosierung OWNER TO jolo;

--
-- TOC entry 247 (class 1259 OID 16761)
-- Name: summe_wirkstoffe_pro_proband_und_tagesmedikation; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW summe_wirkstoffe_pro_proband_und_tagesmedikation AS
 SELECT tagesdosierung.wirkstoffklasse,
    tagesdosierung.wirkstoff,
    sum(tagesdosierung.tagesdosis) AS gesamttagesdosis,
    tagesdosierung.masseinheit,
    tagesdosierung.projekt,
    tagesdosierung.kampagne,
    tagesdosierung.survey_id
   FROM tagesdosierung
  GROUP BY tagesdosierung.projekt, tagesdosierung.kampagne, tagesdosierung.survey_id, tagesdosierung.wirkstoffklasse, tagesdosierung.wirkstoff, tagesdosierung.masseinheit
  ORDER BY tagesdosierung.wirkstoffklasse, tagesdosierung.wirkstoff, sum(tagesdosierung.tagesdosis);


ALTER TABLE summe_wirkstoffe_pro_proband_und_tagesmedikation OWNER TO jolo;

--
-- TOC entry 248 (class 1259 OID 16765)
-- Name: wirkstoffe_in_tagesmedikation; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW wirkstoffe_in_tagesmedikation AS
 SELECT m.name AS wirkstoff,
    count(1) AS anzahl_verordnungen
   FROM ((((((core.molecule m
     JOIN core.prescribeable_drug_composition pdc ON ((m.id = pdc.molecule_id)))
     JOIN core.prescribeable_drug pd ON ((pdc.prescribeable_drug_id = pd.id)))
     JOIN core.regular_prescription rp ON ((pd.id = rp.prescribeable_drug_id)))
     JOIN core.survey s ON ((rp.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project p ON ((c.project_id = p.id)))
  GROUP BY m.name
  ORDER BY count(1) DESC, m.name;


ALTER TABLE wirkstoffe_in_tagesmedikation OWNER TO jolo;

SET search_path = core, pg_catalog;

--
-- TOC entry 2279 (class 2604 OID 16770)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY administration_method ALTER COLUMN id SET DEFAULT nextval('administration_method_id_seq'::regclass);


--
-- TOC entry 2349 (class 2604 OID 17002)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY age_class ALTER COLUMN id SET DEFAULT nextval('age_class_id_seq'::regclass);


--
-- TOC entry 2284 (class 2604 OID 16771)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY campaign ALTER COLUMN id SET DEFAULT nextval('campaign_id_seq'::regclass);


--
-- TOC entry 2359 (class 2604 OID 17129)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY cgi ALTER COLUMN id SET DEFAULT nextval('cgi_id_seq'::regclass);


--
-- TOC entry 2288 (class 2604 OID 16772)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY channel_into_patient ALTER COLUMN id SET DEFAULT nextval('channel_into_patient_id_seq'::regclass);


--
-- TOC entry 2353 (class 2604 OID 17030)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY collateral_effect ALTER COLUMN id SET DEFAULT nextval('collateral_effect_id_seq'::regclass);


--
-- TOC entry 2296 (class 2604 OID 16773)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY drug ALTER COLUMN id SET DEFAULT nextval('drug_id_seq'::regclass);


--
-- TOC entry 2363 (class 2604 OID 17167)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY fps ALTER COLUMN id SET DEFAULT nextval('fps_id_seq'::regclass);


--
-- TOC entry 2361 (class 2604 OID 17148)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY gaf ALTER COLUMN id SET DEFAULT nextval('gaf_id_seq'::regclass);


--
-- TOC entry 2346 (class 2604 OID 16987)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_diagnosis ALTER COLUMN id SET DEFAULT nextval('icd10_diagnosis_id_seq'::regclass);


--
-- TOC entry 2356 (class 2604 OID 17065)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey ALTER COLUMN id SET DEFAULT nextval('icd10_survey_id_seq'::regclass);


--
-- TOC entry 2299 (class 2604 OID 16774)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule ALTER COLUMN id SET DEFAULT nextval('molecule_id_seq'::regclass);


--
-- TOC entry 2302 (class 2604 OID 16775)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule_class ALTER COLUMN id SET DEFAULT nextval('molecule_class_id_seq'::regclass);


--
-- TOC entry 2344 (class 2604 OID 16973)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY organization_unit ALTER COLUMN id SET DEFAULT nextval('organization_unit_id_seq'::regclass);


--
-- TOC entry 2308 (class 2604 OID 16776)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level ALTER COLUMN id SET DEFAULT nextval('plasmatic_level_id_seq'::regclass);


--
-- TOC entry 2309 (class 2604 OID 16777)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug ALTER COLUMN id SET DEFAULT nextval('prescribeable_drug_id_seq'::regclass);


--
-- TOC entry 2312 (class 2604 OID 16778)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition ALTER COLUMN id SET DEFAULT nextval('prescribeable_drug_composition_id_seq'::regclass);


--
-- TOC entry 2315 (class 2604 OID 16779)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY proband ALTER COLUMN id SET DEFAULT nextval('proband_id_seq'::regclass);


--
-- TOC entry 2321 (class 2604 OID 16780)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY project ALTER COLUMN id SET DEFAULT nextval('project_id_seq'::regclass);


--
-- TOC entry 2331 (class 2604 OID 16781)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY sex ALTER COLUMN id SET DEFAULT nextval('sex_id_seq'::regclass);


--
-- TOC entry 2351 (class 2604 OID 17016)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY smoking_habit ALTER COLUMN id SET DEFAULT nextval('smoking_habit_id_seq'::regclass);


--
-- TOC entry 2334 (class 2604 OID 16782)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey ALTER COLUMN id SET DEFAULT nextval('survey_id_seq'::regclass);


--
-- TOC entry 2357 (class 2604 OID 17082)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect ALTER COLUMN id SET DEFAULT nextval('survey_collateral_effect_id_seq'::regclass);


--
-- TOC entry 2340 (class 2604 OID 16783)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_info ALTER COLUMN id SET DEFAULT nextval('survey_info_id_seq'::regclass);


--
-- TOC entry 2342 (class 2604 OID 16784)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY unit ALTER COLUMN id SET DEFAULT nextval('unit_id_seq'::regclass);


--
-- TOC entry 2365 (class 2604 OID 17186)
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY who_qol ALTER COLUMN id SET DEFAULT nextval('who_qol_id_seq'::regclass);


--
-- TOC entry 2368 (class 2606 OID 16786)
-- Name: administration_method_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_name_key UNIQUE (name);


--
-- TOC entry 2370 (class 2606 OID 16788)
-- Name: administration_method_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_pkey PRIMARY KEY (id);


--
-- TOC entry 2448 (class 2606 OID 17010)
-- Name: age_class_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY age_class
    ADD CONSTRAINT age_class_name_key UNIQUE (name);


--
-- TOC entry 2450 (class 2606 OID 17008)
-- Name: age_class_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY age_class
    ADD CONSTRAINT age_class_pkey PRIMARY KEY (id);


--
-- TOC entry 2372 (class 2606 OID 16790)
-- Name: campaign_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_name_key UNIQUE (name);


--
-- TOC entry 2374 (class 2606 OID 16792)
-- Name: campaign_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_pkey PRIMARY KEY (id);


--
-- TOC entry 2376 (class 2606 OID 16794)
-- Name: campaign_project_id_start_date_end_date_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_project_id_start_date_end_date_key UNIQUE (project_id, start_date, end_date);


--
-- TOC entry 2466 (class 2606 OID 17135)
-- Name: cgi_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_pkey PRIMARY KEY (id);


--
-- TOC entry 2468 (class 2606 OID 17137)
-- Name: cgi_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_survey_id_key UNIQUE (survey_id);


--
-- TOC entry 2378 (class 2606 OID 16796)
-- Name: channel_into_patient_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY channel_into_patient
    ADD CONSTRAINT channel_into_patient_name_key UNIQUE (name);


--
-- TOC entry 2380 (class 2606 OID 16798)
-- Name: channel_into_patient_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY channel_into_patient
    ADD CONSTRAINT channel_into_patient_pkey PRIMARY KEY (id);


--
-- TOC entry 2456 (class 2606 OID 17038)
-- Name: collateral_effect_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY collateral_effect
    ADD CONSTRAINT collateral_effect_name_key UNIQUE (name);


--
-- TOC entry 2458 (class 2606 OID 17036)
-- Name: collateral_effect_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY collateral_effect
    ADD CONSTRAINT collateral_effect_pkey PRIMARY KEY (id);


--
-- TOC entry 2382 (class 2606 OID 16800)
-- Name: depot_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_pkey PRIMARY KEY (id);


--
-- TOC entry 2384 (class 2606 OID 16802)
-- Name: depot_prescription_survey_id_prescribeable_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_survey_id_prescribeable_drug_id_key UNIQUE (survey_id, prescribeable_drug_id);


--
-- TOC entry 2386 (class 2606 OID 16804)
-- Name: drug_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY drug
    ADD CONSTRAINT drug_name_key UNIQUE (name);


--
-- TOC entry 2388 (class 2606 OID 16806)
-- Name: drug_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY drug
    ADD CONSTRAINT drug_pkey PRIMARY KEY (id);


--
-- TOC entry 2474 (class 2606 OID 17173)
-- Name: fps_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_pkey PRIMARY KEY (id);


--
-- TOC entry 2476 (class 2606 OID 17175)
-- Name: fps_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_survey_id_key UNIQUE (survey_id);


--
-- TOC entry 2470 (class 2606 OID 17154)
-- Name: gaf_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_pkey PRIMARY KEY (id);


--
-- TOC entry 2472 (class 2606 OID 17156)
-- Name: gaf_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_survey_id_key UNIQUE (survey_id);


--
-- TOC entry 2444 (class 2606 OID 16996)
-- Name: icd10_diagnosis_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_diagnosis
    ADD CONSTRAINT icd10_diagnosis_name_key UNIQUE (name);


--
-- TOC entry 2446 (class 2606 OID 16994)
-- Name: icd10_diagnosis_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_diagnosis
    ADD CONSTRAINT icd10_diagnosis_pkey PRIMARY KEY (id);


--
-- TOC entry 2460 (class 2606 OID 17052)
-- Name: icd10_survey_icd10_diagnosis_id_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_icd10_diagnosis_id_survey_id_key UNIQUE (icd10_diagnosis_id, survey_id);


--
-- TOC entry 2394 (class 2606 OID 16808)
-- Name: molecule_class_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_class
    ADD CONSTRAINT molecule_class_name_key UNIQUE (name);


--
-- TOC entry 2396 (class 2606 OID 16810)
-- Name: molecule_class_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_class
    ADD CONSTRAINT molecule_class_pkey PRIMARY KEY (id);


--
-- TOC entry 2390 (class 2606 OID 16812)
-- Name: molecule_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_name_key UNIQUE (name);


--
-- TOC entry 2392 (class 2606 OID 16814)
-- Name: molecule_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_pkey PRIMARY KEY (id);


--
-- TOC entry 2398 (class 2606 OID 16816)
-- Name: optional_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_pkey PRIMARY KEY (id);


--
-- TOC entry 2400 (class 2606 OID 16818)
-- Name: optional_prescription_survey_id_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_survey_id_drug_id_key UNIQUE (survey_id, drug_id);


--
-- TOC entry 2440 (class 2606 OID 16981)
-- Name: organization_unit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY organization_unit
    ADD CONSTRAINT organization_unit_name_key UNIQUE (name);


--
-- TOC entry 2442 (class 2606 OID 16979)
-- Name: organization_unit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY organization_unit
    ADD CONSTRAINT organization_unit_pkey PRIMARY KEY (id);


--
-- TOC entry 2462 (class 2606 OID 17074)
-- Name: pk_icd10_survey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT pk_icd10_survey PRIMARY KEY (id);


--
-- TOC entry 2402 (class 2606 OID 16820)
-- Name: plasmatic_level_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_pkey PRIMARY KEY (id);


--
-- TOC entry 2410 (class 2606 OID 16822)
-- Name: prescribeable_drug_compositio_prescribeable_drug_id_molecul_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_compositio_prescribeable_drug_id_molecul_key UNIQUE (prescribeable_drug_id, molecule_id);


--
-- TOC entry 2412 (class 2606 OID 16824)
-- Name: prescribeable_drug_composition_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_pkey PRIMARY KEY (id);


--
-- TOC entry 2404 (class 2606 OID 16826)
-- Name: prescribeable_drug_dosage_dosage_unit_id_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_dosage_dosage_unit_id_drug_id_key UNIQUE (dosage, dosage_unit_id, drug_id);


--
-- TOC entry 2406 (class 2606 OID 16828)
-- Name: prescribeable_drug_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_name_key UNIQUE (name);


--
-- TOC entry 2408 (class 2606 OID 16830)
-- Name: prescribeable_drug_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_pkey PRIMARY KEY (id);


--
-- TOC entry 2414 (class 2606 OID 16832)
-- Name: proband_external_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY proband
    ADD CONSTRAINT proband_external_id_key UNIQUE (external_id);


--
-- TOC entry 2416 (class 2606 OID 16834)
-- Name: proband_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY proband
    ADD CONSTRAINT proband_pkey PRIMARY KEY (id);


--
-- TOC entry 2418 (class 2606 OID 16836)
-- Name: project_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY project
    ADD CONSTRAINT project_name_key UNIQUE (name);


--
-- TOC entry 2420 (class 2606 OID 16838)
-- Name: project_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY project
    ADD CONSTRAINT project_pkey PRIMARY KEY (id);


--
-- TOC entry 2422 (class 2606 OID 16840)
-- Name: regular_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_pkey PRIMARY KEY (id);


--
-- TOC entry 2424 (class 2606 OID 16842)
-- Name: regular_prescription_survey_id_prescribeable_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_survey_id_prescribeable_drug_id_key UNIQUE (survey_id, prescribeable_drug_id);


--
-- TOC entry 2426 (class 2606 OID 16844)
-- Name: sex_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY sex
    ADD CONSTRAINT sex_name_key UNIQUE (name);


--
-- TOC entry 2428 (class 2606 OID 16846)
-- Name: sex_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY sex
    ADD CONSTRAINT sex_pkey PRIMARY KEY (id);


--
-- TOC entry 2452 (class 2606 OID 17024)
-- Name: smoking_habit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY smoking_habit
    ADD CONSTRAINT smoking_habit_name_key UNIQUE (name);


--
-- TOC entry 2454 (class 2606 OID 17022)
-- Name: smoking_habit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY smoking_habit
    ADD CONSTRAINT smoking_habit_pkey PRIMARY KEY (id);


--
-- TOC entry 2464 (class 2606 OID 17088)
-- Name: survey_collateral_effect_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_pkey PRIMARY KEY (id);


--
-- TOC entry 2434 (class 2606 OID 16848)
-- Name: survey_info_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey_info
    ADD CONSTRAINT survey_info_pkey PRIMARY KEY (id);


--
-- TOC entry 2430 (class 2606 OID 16850)
-- Name: survey_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_pkey PRIMARY KEY (id);


--
-- TOC entry 2432 (class 2606 OID 16852)
-- Name: survey_proband_id_campaign_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_proband_id_campaign_id_key UNIQUE (proband_id, campaign_id);


--
-- TOC entry 2436 (class 2606 OID 16854)
-- Name: unit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY unit
    ADD CONSTRAINT unit_name_key UNIQUE (name);


--
-- TOC entry 2438 (class 2606 OID 16856)
-- Name: unit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY unit
    ADD CONSTRAINT unit_pkey PRIMARY KEY (id);


--
-- TOC entry 2478 (class 2606 OID 17192)
-- Name: who_qol_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_pkey PRIMARY KEY (id);


--
-- TOC entry 2480 (class 2606 OID 17194)
-- Name: who_qol_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_survey_id_key UNIQUE (survey_id);


--
-- TOC entry 2481 (class 2606 OID 16857)
-- Name: administration_method_channel_into_patient_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_channel_into_patient_id_fkey FOREIGN KEY (channel_into_patient_id) REFERENCES channel_into_patient(id);


--
-- TOC entry 2482 (class 2606 OID 16862)
-- Name: campaign_project_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_project_id_fkey FOREIGN KEY (project_id) REFERENCES project(id);


--
-- TOC entry 2507 (class 2606 OID 17138)
-- Name: cgi_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2483 (class 2606 OID 16867)
-- Name: depot_prescription_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- TOC entry 2484 (class 2606 OID 16872)
-- Name: depot_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2509 (class 2606 OID 17176)
-- Name: fps_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2508 (class 2606 OID 17157)
-- Name: gaf_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2503 (class 2606 OID 17053)
-- Name: icd10_survey_icd10_diagnosis_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_icd10_diagnosis_id_fkey FOREIGN KEY (icd10_diagnosis_id) REFERENCES icd10_diagnosis(id);


--
-- TOC entry 2504 (class 2606 OID 17058)
-- Name: icd10_survey_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2485 (class 2606 OID 16877)
-- Name: molecule_molecule_class_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_molecule_class_id_fkey FOREIGN KEY (molecule_class_id) REFERENCES molecule_class(id);


--
-- TOC entry 2486 (class 2606 OID 16882)
-- Name: optional_prescription_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_drug_id_fkey FOREIGN KEY (drug_id) REFERENCES drug(id);


--
-- TOC entry 2487 (class 2606 OID 16887)
-- Name: optional_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2488 (class 2606 OID 16892)
-- Name: plasmatic_level_molecule_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_molecule_id_fkey FOREIGN KEY (molecule_id) REFERENCES molecule(id);


--
-- TOC entry 2489 (class 2606 OID 16897)
-- Name: plasmatic_level_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2490 (class 2606 OID 16902)
-- Name: plasmatic_level_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_unit_id_fkey FOREIGN KEY (unit_id) REFERENCES unit(id);


--
-- TOC entry 2491 (class 2606 OID 16907)
-- Name: prescribeable_drug_administration_method_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_administration_method_id_fkey FOREIGN KEY (administration_method_id) REFERENCES administration_method(id);


--
-- TOC entry 2494 (class 2606 OID 16912)
-- Name: prescribeable_drug_composition_amount_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_amount_unit_id_fkey FOREIGN KEY (amount_unit_id) REFERENCES unit(id);


--
-- TOC entry 2495 (class 2606 OID 16917)
-- Name: prescribeable_drug_composition_molecule_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_molecule_id_fkey FOREIGN KEY (molecule_id) REFERENCES molecule(id);


--
-- TOC entry 2496 (class 2606 OID 16922)
-- Name: prescribeable_drug_composition_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- TOC entry 2492 (class 2606 OID 16927)
-- Name: prescribeable_drug_dosage_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_dosage_unit_id_fkey FOREIGN KEY (dosage_unit_id) REFERENCES unit(id);


--
-- TOC entry 2493 (class 2606 OID 16932)
-- Name: prescribeable_drug_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_drug_id_fkey FOREIGN KEY (drug_id) REFERENCES drug(id);


--
-- TOC entry 2497 (class 2606 OID 16937)
-- Name: proband_sex_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY proband
    ADD CONSTRAINT proband_sex_id_fkey FOREIGN KEY (sex_id) REFERENCES sex(id);


--
-- TOC entry 2498 (class 2606 OID 16942)
-- Name: regular_prescription_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- TOC entry 2499 (class 2606 OID 16947)
-- Name: regular_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2500 (class 2606 OID 16952)
-- Name: survey_campaign_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_campaign_id_fkey FOREIGN KEY (campaign_id) REFERENCES campaign(id);


--
-- TOC entry 2506 (class 2606 OID 17094)
-- Name: survey_collateral_effect_collateral_effect_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_collateral_effect_id_fkey FOREIGN KEY (collateral_effect_id) REFERENCES collateral_effect(id);


--
-- TOC entry 2505 (class 2606 OID 17089)
-- Name: survey_collateral_effect_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2502 (class 2606 OID 16957)
-- Name: survey_info_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_info
    ADD CONSTRAINT survey_info_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2501 (class 2606 OID 16962)
-- Name: survey_proband_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_proband_id_fkey FOREIGN KEY (proband_id) REFERENCES proband(id);


--
-- TOC entry 2510 (class 2606 OID 17195)
-- Name: who_qol_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- TOC entry 2667 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2015-11-13 11:07:41 CET

--
-- PostgreSQL database dump complete
--

