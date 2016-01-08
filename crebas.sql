--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: agate; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA agate;


ALTER SCHEMA agate OWNER TO jolo;

--
-- Name: core; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA core;


ALTER SCHEMA core OWNER TO jolo;

--
-- Name: corestat; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA corestat;


ALTER SCHEMA corestat OWNER TO jolo;

--
-- Name: forensics; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA forensics;


ALTER SCHEMA forensics OWNER TO jolo;

--
-- Name: forstat; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA forstat;


ALTER SCHEMA forstat OWNER TO jolo;

--
-- Name: geo; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA geo;


ALTER SCHEMA geo OWNER TO jolo;

--
-- Name: stat; Type: SCHEMA; Schema: -; Owner: jolo
--

CREATE SCHEMA stat;


ALTER SCHEMA stat OWNER TO jolo;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


SET search_path = core, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
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

SET search_path = agate, pg_catalog;

--
-- Name: all_depot_prescriptions; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW all_depot_prescriptions AS
 SELECT s.id AS survey_id,
    pd.name AS prescribeable_drug_name,
    dp.dosage AS dosage_in_mg,
    dp.injection_interval_in_days,
    dp.last_injection_on AS last_injection_date,
    d.name AS drug_name
   FROM (((((core.survey s
     JOIN core.campaign camp ON ((s.campaign_id = camp.id)))
     JOIN core.project proj ON ((camp.project_id = proj.id)))
     JOIN core.depot_prescription dp ON ((s.id = dp.survey_id)))
     JOIN core.prescribeable_drug pd ON ((dp.prescribeable_drug_id = pd.id)))
     JOIN core.drug d ON ((pd.drug_id = d.id)))
  WHERE (proj.name ~~ 'AGATE%'::text)
  ORDER BY s.id;


ALTER TABLE all_depot_prescriptions OWNER TO jolo;

SET search_path = core, pg_catalog;

--
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
-- Name: icd10_survey; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE icd10_survey (
    icd10_diagnosis_id integer NOT NULL,
    survey_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    id integer NOT NULL
);


ALTER TABLE icd10_survey OWNER TO jolo;

SET search_path = agate, pg_catalog;

--
-- Name: all_diagnosis; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW all_diagnosis AS
 SELECT s.id AS survey_id,
    i.name AS diagnosis_name,
    i.id AS diagnosis_id
   FROM ((core.survey s
     JOIN core.icd10_survey ids ON ((s.id = ids.survey_id)))
     JOIN core.icd10_diagnosis i ON ((ids.icd10_diagnosis_id = i.id)))
  ORDER BY s.id, i.name;


ALTER TABLE all_diagnosis OWNER TO jolo;

SET search_path = core, pg_catalog;

--
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
-- Name: molecule_prescription; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE molecule_prescription (
    id integer NOT NULL,
    molecule_id integer NOT NULL,
    survey_id integer NOT NULL,
    dosage_in_mg numeric
);


ALTER TABLE molecule_prescription OWNER TO jolo;

SET search_path = agate, pg_catalog;

--
-- Name: all_molecule_prescriptions; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW all_molecule_prescriptions AS
 SELECT m.name AS molecule,
    mp.dosage_in_mg,
    s.id AS survey_id,
    m.id AS molecule_id
   FROM ((((core.survey s
     JOIN core.molecule_prescription mp ON ((s.id = mp.survey_id)))
     JOIN core.molecule m ON ((mp.molecule_id = m.id)))
     JOIN core.campaign camp ON ((s.campaign_id = camp.id)))
     JOIN core.project proj ON ((camp.project_id = proj.id)))
  WHERE (proj.name ~~ 'AGATE%'::text)
  ORDER BY m.name, mp.dosage_in_mg;


ALTER TABLE all_molecule_prescriptions OWNER TO jolo;

SET search_path = core, pg_catalog;

--
-- Name: proband; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE proband (
    id integer NOT NULL,
    external_id integer,
    birthday date,
    height_in_cm integer,
    sex_id integer NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    surname text DEFAULT ''::text NOT NULL,
    first_name text DEFAULT ''::text NOT NULL,
    year_of_birth integer
);


ALTER TABLE proband OWNER TO jolo;

--
-- Name: sex; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE sex (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT sex_name_check CHECK ((length(name) >= 1))
);


ALTER TABLE sex OWNER TO jolo;

SET search_path = agate, pg_catalog;

--
-- Name: all_surveys; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW all_surveys AS
 SELECT proj.name AS project_name,
    camp.name AS campaign_name,
    prob.year_of_birth AS proband_year_of_birth,
    sex.name AS proband_sex,
    surv.survey_date,
    surv.id AS survey_id
   FROM ((((core.project proj
     JOIN core.campaign camp ON ((proj.id = camp.project_id)))
     JOIN core.survey surv ON ((camp.id = surv.campaign_id)))
     JOIN core.proband prob ON ((surv.proband_id = prob.id)))
     JOIN core.sex sex ON ((prob.sex_id = sex.id)))
  WHERE (proj.name ~~ 'AGATE%'::text)
  ORDER BY proj.name, camp.name, prob.year_of_birth;


ALTER TABLE all_surveys OWNER TO jolo;

--
-- Name: diagnosis_count; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW diagnosis_count AS
 SELECT p.name AS "Project",
    icd10.name AS "Diagnosis Name",
    count(1) AS "Count"
   FROM ((((core.icd10_diagnosis icd10
     JOIN core.icd10_survey s_icd10 ON ((icd10.id = s_icd10.icd10_diagnosis_id)))
     JOIN core.survey s ON ((s_icd10.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project p ON ((c.project_id = p.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, icd10.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE diagnosis_count OWNER TO jolo;

--
-- Name: diagnosis_count_per_campaign; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW diagnosis_count_per_campaign AS
 SELECT p.name AS "Project",
    c.name AS "Campaign",
    icd10.name AS "Diagnosis Name",
    count(1) AS "Count"
   FROM ((((core.icd10_diagnosis icd10
     JOIN core.icd10_survey s_icd10 ON ((icd10.id = s_icd10.icd10_diagnosis_id)))
     JOIN core.survey s ON ((s_icd10.survey_id = s.id)))
     JOIN core.campaign c ON ((s.campaign_id = c.id)))
     JOIN core.project p ON ((c.project_id = p.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, c.name, icd10.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE diagnosis_count_per_campaign OWNER TO jolo;

SET search_path = core, pg_catalog;

--
-- Name: molecule_class; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE molecule_class (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT molecule_class_name_check CHECK ((length(name) > 1))
);


ALTER TABLE molecule_class OWNER TO jolo;

SET search_path = agate, pg_catalog;

--
-- Name: molecule_class_prescription_count; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW molecule_class_prescription_count AS
 SELECT p.name AS "Project",
    mc.name AS "Molecule Class",
    count(1) AS "Prescription Count"
   FROM (((((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.molecule_prescription mp ON ((s.id = mp.survey_id)))
     JOIN core.molecule m ON ((mp.molecule_id = m.id)))
     JOIN core.molecule_class mc ON ((m.molecule_class_id = mc.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, mc.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE molecule_class_prescription_count OWNER TO jolo;

--
-- Name: molecule_class_prescription_per_campaign_count; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW molecule_class_prescription_per_campaign_count AS
 SELECT p.name AS "Project",
    c.name AS "Campaign",
    mc.name AS "Molecule Class",
    count(1) AS "Prescription Count"
   FROM (((((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.molecule_prescription mp ON ((s.id = mp.survey_id)))
     JOIN core.molecule m ON ((mp.molecule_id = m.id)))
     JOIN core.molecule_class mc ON ((m.molecule_class_id = mc.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, c.name, mc.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE molecule_class_prescription_per_campaign_count OWNER TO jolo;

--
-- Name: molecule_prescription_count; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW molecule_prescription_count AS
 SELECT p.name AS "Project",
    m.name AS "Molecule",
    count(1) AS "Prescription Count"
   FROM ((((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.molecule_prescription mp ON ((s.id = mp.survey_id)))
     JOIN core.molecule m ON ((mp.molecule_id = m.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, m.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE molecule_prescription_count OWNER TO jolo;

--
-- Name: molecule_prescription_per_campaign_count; Type: VIEW; Schema: agate; Owner: jolo
--

CREATE VIEW molecule_prescription_per_campaign_count AS
 SELECT p.name AS "Project",
    c.name AS "Campaign",
    m.name AS "Molecule",
    count(1) AS "Prescription Count"
   FROM ((((core.project p
     JOIN core.campaign c ON ((p.id = c.project_id)))
     JOIN core.survey s ON ((c.id = s.campaign_id)))
     JOIN core.molecule_prescription mp ON ((s.id = mp.survey_id)))
     JOIN core.molecule m ON ((mp.molecule_id = m.id)))
  WHERE (p.name ~~ '%AGATE%'::text)
  GROUP BY p.name, c.name, m.name
  ORDER BY p.name, count(1) DESC;


ALTER TABLE molecule_prescription_per_campaign_count OWNER TO jolo;

SET search_path = core, pg_catalog;

--
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
-- Name: administration_method_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE administration_method_id_seq OWNED BY administration_method.id;


--
-- Name: age_class; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE age_class (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE age_class OWNER TO jolo;

--
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
-- Name: age_class_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE age_class_id_seq OWNED BY age_class.id;


--
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
-- Name: campaign_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE campaign_id_seq OWNED BY campaign.id;


--
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
-- Name: cgi_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE cgi_id_seq OWNED BY cgi.id;


--
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
-- Name: channel_into_patient_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE channel_into_patient_id_seq OWNED BY channel_into_patient.id;


--
-- Name: collateral_effect; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE collateral_effect (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE collateral_effect OWNER TO jolo;

--
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
-- Name: collateral_effect_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE collateral_effect_id_seq OWNED BY collateral_effect.id;


--
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
-- Name: drug_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE drug_id_seq OWNED BY drug.id;


--
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
-- Name: fps_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE fps_id_seq OWNED BY fps.id;


--
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
-- Name: gaf_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE gaf_id_seq OWNED BY gaf.id;


--
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
-- Name: icd10_diagnosis_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE icd10_diagnosis_id_seq OWNED BY icd10_diagnosis.id;


--
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
-- Name: icd10_survey_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE icd10_survey_id_seq OWNED BY icd10_survey.id;


--
-- Name: information_source_type; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE information_source_type (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT information_source_type_name_check CHECK ((length(name) > 1))
);


ALTER TABLE information_source_type OWNER TO jolo;

--
-- Name: information_source_type_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE information_source_type_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE information_source_type_id_seq OWNER TO jolo;

--
-- Name: information_source_type_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE information_source_type_id_seq OWNED BY information_source_type.id;


--
-- Name: job; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE job (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT job_name_check CHECK ((length(name) > 1))
);


ALTER TABLE job OWNER TO jolo;

--
-- Name: job_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE job_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE job_id_seq OWNER TO jolo;

--
-- Name: job_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE job_id_seq OWNED BY job.id;


--
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
-- Name: molecule_class_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE molecule_class_id_seq OWNED BY molecule_class.id;


--
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
-- Name: molecule_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE molecule_id_seq OWNED BY molecule.id;


--
-- Name: molecule_prescription_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE molecule_prescription_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE molecule_prescription_id_seq OWNER TO jolo;

--
-- Name: molecule_prescription_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE molecule_prescription_id_seq OWNED BY molecule_prescription.id;


--
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
-- Name: organization_unit; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE organization_unit (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE organization_unit OWNER TO jolo;

--
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
-- Name: organization_unit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE organization_unit_id_seq OWNED BY organization_unit.id;


--
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
-- Name: plasmatic_level_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE plasmatic_level_id_seq OWNED BY plasmatic_level.id;


--
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
-- Name: prescribeable_drug_composition_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE prescribeable_drug_composition_id_seq OWNED BY prescribeable_drug_composition.id;


--
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
-- Name: prescribeable_drug_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE prescribeable_drug_id_seq OWNED BY prescribeable_drug.id;


--
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
-- Name: proband_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE proband_id_seq OWNED BY proband.id;


--
-- Name: processing_status; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE processing_status (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT processing_status_name_check CHECK ((length(name) >= 1))
);


ALTER TABLE processing_status OWNER TO jolo;

--
-- Name: processing_status_id_seq; Type: SEQUENCE; Schema: core; Owner: jolo
--

CREATE SEQUENCE processing_status_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE processing_status_id_seq OWNER TO jolo;

--
-- Name: processing_status_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE processing_status_id_seq OWNED BY processing_status.id;


--
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
-- Name: project_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE project_id_seq OWNED BY project.id;


--
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
-- Name: sex_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE sex_id_seq OWNED BY sex.id;


--
-- Name: smoking_habit; Type: TABLE; Schema: core; Owner: jolo; Tablespace: 
--

CREATE TABLE smoking_habit (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL
);


ALTER TABLE smoking_habit OWNER TO jolo;

--
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
-- Name: smoking_habit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE smoking_habit_id_seq OWNED BY smoking_habit.id;


--
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
-- Name: survey_collateral_effect_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_collateral_effect_id_seq OWNED BY survey_collateral_effect.id;


--
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
-- Name: survey_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_id_seq OWNED BY survey.id;


--
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
-- Name: TABLE survey_info; Type: COMMENT; Schema: core; Owner: jolo
--

COMMENT ON TABLE survey_info IS 'add additional uncathegorized info to this table!';


--
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
-- Name: survey_info_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE survey_info_id_seq OWNED BY survey_info.id;


--
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
-- Name: unit_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE unit_id_seq OWNED BY unit.id;


--
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
-- Name: who_qol_id_seq; Type: SEQUENCE OWNED BY; Schema: core; Owner: jolo
--

ALTER SEQUENCE who_qol_id_seq OWNED BY who_qol.id;


SET search_path = corestat, pg_catalog;

--
-- Name: available_reports; Type: VIEW; Schema: corestat; Owner: jolo
--

CREATE VIEW available_reports AS
 SELECT (((n.nspname)::text || '.'::text) || (c.relname)::text) AS "Report Name",
    obj_description(c.oid, 'pg_class'::name) AS "Description",
        CASE c.relkind
            WHEN 'r'::"char" THEN 'table'::text
            WHEN 'v'::"char" THEN 'view'::text
            WHEN 'm'::"char" THEN 'materialized view'::text
            ELSE NULL::text
        END AS "Report Type"
   FROM (pg_class c
     JOIN pg_namespace n ON ((n.oid = c.relnamespace)))
  WHERE (((c.relkind = ANY (ARRAY['r'::"char", 'v'::"char", 'm'::"char"])) AND (n.nspname !~ '^pg_toast'::text)) AND (n.nspname = ANY (ARRAY['forstat'::name, 'stat'::name, 'corestat'::name, 'agate'::name, 'core'::name])))
  ORDER BY (((n.nspname)::text || '.'::text) || (c.relname)::text), obj_description(c.oid, 'pg_class'::name);


ALTER TABLE available_reports OWNER TO jolo;

SET search_path = forensics, pg_catalog;

--
-- Name: consultancy_result; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE consultancy_result (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT consultancy_result_name_check CHECK ((length(name) > 1))
);


ALTER TABLE consultancy_result OWNER TO jolo;

--
-- Name: consultancy_result_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE consultancy_result_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE consultancy_result_id_seq OWNER TO jolo;

--
-- Name: consultancy_result_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE consultancy_result_id_seq OWNED BY consultancy_result.id;


--
-- Name: crime_case; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE crime_case (
    id integer NOT NULL,
    name text NOT NULL,
    city_id integer,
    housing_type_id integer,
    crime_year integer,
    crime_date date,
    crime_time time without time zone,
    description text DEFAULT ''::text NOT NULL,
    processing_status_id integer,
    CONSTRAINT crime_case_name_check CHECK ((length(name) > 1))
);


ALTER TABLE crime_case OWNER TO jolo;

--
-- Name: crime_case_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE crime_case_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE crime_case_id_seq OWNER TO jolo;

--
-- Name: crime_case_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE crime_case_id_seq OWNED BY crime_case.id;


--
-- Name: crime_case_participant; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE crime_case_participant (
    id integer NOT NULL,
    crime_case_party_role_id integer NOT NULL,
    crime_case_id integer NOT NULL,
    name text DEFAULT ''::text NOT NULL,
    sex_id integer,
    age_in_years integer,
    has_precedent_convictions boolean DEFAULT false NOT NULL,
    crime_type_id integer,
    modus_operandi_id integer,
    mental_disease_id integer,
    crime_motive_id integer,
    consultancy_result_id integer,
    weapon_id integer,
    description text DEFAULT ''::text NOT NULL,
    job_id integer,
    is_drug_intoxicated boolean DEFAULT false,
    is_alcohol_intoxicated boolean DEFAULT false,
    legally_owns_weapon boolean DEFAULT false NOT NULL,
    has_long_conflict_history boolean DEFAULT false NOT NULL
);


ALTER TABLE crime_case_participant OWNER TO jolo;

--
-- Name: crime_case_participant_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE crime_case_participant_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE crime_case_participant_id_seq OWNER TO jolo;

--
-- Name: crime_case_participant_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE crime_case_participant_id_seq OWNED BY crime_case_participant.id;


--
-- Name: crime_case_party_role; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE crime_case_party_role (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT crime_case_party_role_name_check CHECK ((length(name) > 1))
);


ALTER TABLE crime_case_party_role OWNER TO jolo;

--
-- Name: crime_case_party_role_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE crime_case_party_role_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE crime_case_party_role_id_seq OWNER TO jolo;

--
-- Name: crime_case_party_role_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE crime_case_party_role_id_seq OWNED BY crime_case_party_role.id;


--
-- Name: crime_motive; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE crime_motive (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT crime_motive_name_check CHECK ((length(name) > 1))
);


ALTER TABLE crime_motive OWNER TO jolo;

--
-- Name: crime_motive_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE crime_motive_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE crime_motive_id_seq OWNER TO jolo;

--
-- Name: crime_motive_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE crime_motive_id_seq OWNED BY crime_motive.id;


--
-- Name: crime_type; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE crime_type (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT crime_type_name_check CHECK ((length(name) > 1))
);


ALTER TABLE crime_type OWNER TO jolo;

--
-- Name: crime_type_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE crime_type_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE crime_type_id_seq OWNER TO jolo;

--
-- Name: crime_type_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE crime_type_id_seq OWNED BY crime_type.id;


--
-- Name: information_source_for_crime_case; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE information_source_for_crime_case (
    id integer NOT NULL,
    information_source_type_id integer NOT NULL,
    crime_case_id integer NOT NULL,
    url text NOT NULL,
    when_added timestamp with time zone DEFAULT now() NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT information_source_for_crime_case_url_check CHECK ((length(url) > 1))
);


ALTER TABLE information_source_for_crime_case OWNER TO jolo;

--
-- Name: information_source_for_crime_case_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE information_source_for_crime_case_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE information_source_for_crime_case_id_seq OWNER TO jolo;

--
-- Name: information_source_for_crime_case_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE information_source_for_crime_case_id_seq OWNED BY information_source_for_crime_case.id;


--
-- Name: mental_disease; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE mental_disease (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT mental_disease_name_check CHECK ((length(name) > 1))
);


ALTER TABLE mental_disease OWNER TO jolo;

--
-- Name: mental_disease_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE mental_disease_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE mental_disease_id_seq OWNER TO jolo;

--
-- Name: mental_disease_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE mental_disease_id_seq OWNED BY mental_disease.id;


--
-- Name: modus_operandi; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE modus_operandi (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT modus_operandi_name_check CHECK ((length(name) > 1))
);


ALTER TABLE modus_operandi OWNER TO jolo;

--
-- Name: modus_operandi_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE modus_operandi_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE modus_operandi_id_seq OWNER TO jolo;

--
-- Name: modus_operandi_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE modus_operandi_id_seq OWNED BY modus_operandi.id;


--
-- Name: weapon; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE weapon (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    weapon_type_id integer NOT NULL,
    CONSTRAINT weapon_name_check CHECK ((length(name) > 1))
);


ALTER TABLE weapon OWNER TO jolo;

--
-- Name: weapon_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE weapon_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE weapon_id_seq OWNER TO jolo;

--
-- Name: weapon_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE weapon_id_seq OWNED BY weapon.id;


--
-- Name: weapon_type; Type: TABLE; Schema: forensics; Owner: jolo; Tablespace: 
--

CREATE TABLE weapon_type (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT weapon_type_name_check CHECK ((length(name) > 1))
);


ALTER TABLE weapon_type OWNER TO jolo;

--
-- Name: weapon_type_id_seq; Type: SEQUENCE; Schema: forensics; Owner: jolo
--

CREATE SEQUENCE weapon_type_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE weapon_type_id_seq OWNER TO jolo;

--
-- Name: weapon_type_id_seq; Type: SEQUENCE OWNED BY; Schema: forensics; Owner: jolo
--

ALTER SEQUENCE weapon_type_id_seq OWNED BY weapon_type.id;


SET search_path = forstat, pg_catalog;

--
-- Name: alcohol_and_drug_intoxications_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW alcohol_and_drug_intoxications_by_role AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(1) AS intoxication_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR ((((ccpr.name = 'Täter'::text) AND (ccp.is_alcohol_intoxicated = true)) AND (ccp.is_drug_intoxicated = true)) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END
  ORDER BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END DESC;


ALTER TABLE alcohol_and_drug_intoxications_by_role OWNER TO jolo;

--
-- Name: alcohol_intoxications_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW alcohol_intoxications_by_role AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(ccp.is_alcohol_intoxicated) AS is_alcohol_intoxicated_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR (((ccpr.name = 'Täter'::text) AND (ccp.is_alcohol_intoxicated = true)) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END
  ORDER BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END DESC;


ALTER TABLE alcohol_intoxications_by_role OWNER TO jolo;

--
-- Name: alcohol_or_drug_intoxications_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW alcohol_or_drug_intoxications_by_role AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(1) AS intoxication_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE (((ccpr.name = 'Opfer'::text) OR ((ccpr.name = 'Täter'::text) AND (ccp.is_alcohol_intoxicated = true))) OR ((ccp.is_drug_intoxicated = true) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END
  ORDER BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END DESC;


ALTER TABLE alcohol_or_drug_intoxications_by_role OWNER TO jolo;

SET search_path = geo, pg_catalog;

--
-- Name: city; Type: TABLE; Schema: geo; Owner: jolo; Tablespace: 
--

CREATE TABLE city (
    id integer NOT NULL,
    name text NOT NULL,
    people_count integer DEFAULT 0 NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    country_id integer NOT NULL,
    CONSTRAINT city_name_check CHECK ((length(name) > 1))
);


ALTER TABLE city OWNER TO jolo;

--
-- Name: housing_type; Type: TABLE; Schema: geo; Owner: jolo; Tablespace: 
--

CREATE TABLE housing_type (
    id integer NOT NULL,
    name text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT housing_type_name_check CHECK ((length(name) > 1))
);


ALTER TABLE housing_type OWNER TO jolo;

SET search_path = forstat, pg_catalog;

--
-- Name: all_crime_cases; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW all_crime_cases AS
 SELECT COALESCE(( SELECT ps.name
           FROM core.processing_status ps
          WHERE (ps.id = cc.processing_status_id)), 'NA'::text) AS processing_status,
    COALESCE(( SELECT cit.name
           FROM geo.city cit
          WHERE (cit.id = cc.city_id)), 'NA'::text) AS city,
    COALESCE(( SELECT ht.name
           FROM geo.housing_type ht
          WHERE (cc.housing_type_id = ht.id)), 'NA'::text) AS housing_type,
    cc.id,
    cc.name,
    cc.city_id,
    cc.housing_type_id,
    cc.crime_year,
    cc.crime_date,
    cc.crime_time,
    cc.description,
    cc.processing_status_id
   FROM forensics.crime_case cc
  ORDER BY COALESCE(( SELECT ps.name
           FROM core.processing_status ps
          WHERE (ps.id = cc.processing_status_id)), 'NA'::text), COALESCE(( SELECT cit.name
           FROM geo.city cit
          WHERE (cit.id = cc.city_id)), 'NA'::text), COALESCE(( SELECT ht.name
           FROM geo.housing_type ht
          WHERE (cc.housing_type_id = ht.id)), 'NA'::text);


ALTER TABLE all_crime_cases OWNER TO jolo;

--
-- Name: VIEW all_crime_cases; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW all_crime_cases IS 'core data for all crime cases';


--
-- Name: anzahl_opfer_pro_fall; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW anzahl_opfer_pro_fall AS
 SELECT q.cnt AS anzahl_opfer,
    count(q.cnt) AS anzahl_faelle
   FROM ( SELECT cc.name AS crime_case,
            count(1) AS cnt
           FROM (((forensics.crime_case_party_role ccpr
             JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
             JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
             JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
          WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
          GROUP BY cc.name
          ORDER BY count(1) DESC) q
  GROUP BY q.cnt;


ALTER TABLE anzahl_opfer_pro_fall OWNER TO jolo;

--
-- Name: anzahl_taeter_pro_fall; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW anzahl_taeter_pro_fall AS
 SELECT q.cnt AS anzahl_taeter,
    count(q.cnt) AS anzahl_faelle
   FROM ( SELECT cc.name AS crime_case,
            count(1) AS cnt
           FROM (((forensics.crime_case_party_role ccpr
             JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
             JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
             JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
          WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
          GROUP BY cc.name
          ORDER BY count(1) DESC) q
  GROUP BY q.cnt;


ALTER TABLE anzahl_taeter_pro_fall OWNER TO jolo;

--
-- Name: berufe_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW berufe_der_opfer AS
 SELECT
        CASE
            WHEN (j.name = 'Arbeitslos'::text) THEN 'Disoccupato'::text
            WHEN (j.name = 'Arbeiter'::text) THEN 'Operaio'::text
            WHEN (j.name = 'Rentner'::text) THEN 'Pensionato'::text
            WHEN (j.name = 'Ingeneur'::text) THEN 'Ingeniere'::text
            WHEN (j.name = 'Künstler'::text) THEN 'Artista'::text
            WHEN (j.name = 'Berufsfahrer (LKW)'::text) THEN 'Camionista'::text
            WHEN (j.name = 'Lehrling'::text) THEN 'Apprendista'::text
            WHEN (j.name = 'Schüler'::text) THEN 'Studente'::text
            WHEN (j.name = 'Handwerker'::text) THEN 'Artigiano'::text
            WHEN (j.name = 'Angestellter'::text) THEN 'Impiegato'::text
            WHEN (j.name = 'Landwirt'::text) THEN 'Agricoltore'::text
            WHEN (j.name = 'Hausfrau'::text) THEN 'Casalinga'::text
            ELSE j.name
        END AS job_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN core.job j ON ((ccp.job_id = j.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY j.name
  ORDER BY count(1) DESC;


ALTER TABLE berufe_der_opfer OWNER TO jolo;

--
-- Name: berufe_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW berufe_der_taeter AS
 SELECT
        CASE
            WHEN (j.name = 'Arbeitslos'::text) THEN 'Disoccupato'::text
            WHEN (j.name = 'Arbeiter'::text) THEN 'Operaio'::text
            WHEN (j.name = 'Rentner'::text) THEN 'Pensionato'::text
            WHEN (j.name = 'Ingeneur'::text) THEN 'Ingeniere'::text
            WHEN (j.name = 'Künstler'::text) THEN 'Artista'::text
            WHEN (j.name = 'Berufsfahrer (LKW)'::text) THEN 'Camionista'::text
            WHEN (j.name = 'Lehrling'::text) THEN 'Apprendista'::text
            WHEN (j.name = 'Schüler'::text) THEN 'Studente'::text
            WHEN (j.name = 'Handwerker'::text) THEN 'Artigiano'::text
            WHEN (j.name = 'Angestellter'::text) THEN 'Impiegato'::text
            WHEN (j.name = 'Landwirt'::text) THEN 'Agricoltore'::text
            WHEN (j.name = 'Hausfrau'::text) THEN 'Casalinga'::text
            ELSE j.name
        END AS job_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN core.job j ON ((ccp.job_id = j.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY j.name
  ORDER BY count(1) DESC;


ALTER TABLE berufe_der_taeter OWNER TO jolo;

--
-- Name: conflict_history_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW conflict_history_by_role AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(ccp.has_long_conflict_history) AS has_long_conflict_history_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR (((ccpr.name = 'Täter'::text) AND (ccp.has_long_conflict_history = true)) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END
  ORDER BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END DESC;


ALTER TABLE conflict_history_by_role OWNER TO jolo;

--
-- Name: count_crime_case_participants_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW count_crime_case_participants_by_role AS
 SELECT ccr.name AS party_role,
    count(ccp.id) AS count
   FROM (forensics.crime_case_participant ccp
     JOIN forensics.crime_case_party_role ccr ON ((ccp.crime_case_party_role_id = ccr.id)))
  GROUP BY ccr.name
  ORDER BY ccr.name;


ALTER TABLE count_crime_case_participants_by_role OWNER TO jolo;

--
-- Name: VIEW count_crime_case_participants_by_role; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW count_crime_case_participants_by_role IS 'count how many parties exist per role';


--
-- Name: count_crime_case_participants_by_sex; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW count_crime_case_participants_by_sex AS
 SELECT s.name AS sex,
    count(ccp.id) AS count
   FROM (forensics.crime_case_participant ccp
     JOIN core.sex s ON ((ccp.sex_id = s.id)))
  GROUP BY s.name
  ORDER BY s.name;


ALTER TABLE count_crime_case_participants_by_sex OWNER TO jolo;

--
-- Name: VIEW count_crime_case_participants_by_sex; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW count_crime_case_participants_by_sex IS 'count how many parties exist per sex';


--
-- Name: count_crime_case_participants_by_sex_and_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW count_crime_case_participants_by_sex_and_by_role AS
 SELECT ccpr.name AS crime_case_party_role,
    s.name AS sex,
    count(ccp.id) AS count
   FROM ((forensics.crime_case_participant ccp
     JOIN core.sex s ON ((ccp.sex_id = s.id)))
     JOIN forensics.crime_case_party_role ccpr ON ((ccp.crime_case_party_role_id = ccpr.id)))
  GROUP BY ccpr.name, s.name
  ORDER BY ccpr.name, s.name;


ALTER TABLE count_crime_case_participants_by_sex_and_by_role OWNER TO jolo;

--
-- Name: VIEW count_crime_case_participants_by_sex_and_by_role; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW count_crime_case_participants_by_sex_and_by_role IS 'count how many parties exist per sex and per role';


--
-- Name: crime_case_count; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_count AS
 SELECT count(1) AS "Anzahl Fälle"
   FROM forensics.crime_case;


ALTER TABLE crime_case_count OWNER TO jolo;

--
-- Name: VIEW crime_case_count; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_count IS 'Anzahl aller cases in der Datenbank';


--
-- Name: crime_case_count_by_city; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_count_by_city AS
 SELECT c.name AS city,
    count(1) AS count
   FROM (forensics.crime_case cc
     JOIN geo.city c ON ((cc.city_id = c.id)))
  GROUP BY c.name
  ORDER BY c.name, count(1);


ALTER TABLE crime_case_count_by_city OWNER TO jolo;

--
-- Name: VIEW crime_case_count_by_city; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_count_by_city IS 'Anzahl aller cases in der Datenbank gruppiert nach Stadt';


SET search_path = geo, pg_catalog;

--
-- Name: country; Type: TABLE; Schema: geo; Owner: jolo; Tablespace: 
--

CREATE TABLE country (
    id integer NOT NULL,
    name text NOT NULL,
    symbol text NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    CONSTRAINT country_name_check CHECK ((length(name) > 1)),
    CONSTRAINT country_symbol_check CHECK ((length(symbol) > 1))
);


ALTER TABLE country OWNER TO jolo;

SET search_path = forstat, pg_catalog;

--
-- Name: crime_case_count_by_country; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_count_by_country AS
 SELECT cn.name AS country,
    count(1) AS count
   FROM ((forensics.crime_case cc
     JOIN geo.city c ON ((cc.city_id = c.id)))
     JOIN geo.country cn ON ((c.country_id = cn.id)))
  GROUP BY cn.name
  ORDER BY cn.name, count(1);


ALTER TABLE crime_case_count_by_country OWNER TO jolo;

--
-- Name: VIEW crime_case_count_by_country; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_count_by_country IS 'Anzahl aller cases in der Datenbank gruppiert nach Land';


--
-- Name: crime_case_count_by_processing_status; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_count_by_processing_status AS
 SELECT ps.name AS status,
    count(1) AS count
   FROM (forensics.crime_case cc
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
  GROUP BY ps.name
  ORDER BY ps.name, count(1);


ALTER TABLE crime_case_count_by_processing_status OWNER TO jolo;

--
-- Name: VIEW crime_case_count_by_processing_status; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_count_by_processing_status IS 'Anzahl aller cases in der Datenbank gruppiert nach Bearbeitungsstatus';


--
-- Name: crime_case_overview; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_overview AS
 SELECT COALESCE(( SELECT ccpr.name
           FROM forensics.crime_case_party_role ccpr
          WHERE (ccpr.id = ccp.crime_case_party_role_id)), 'NA'::text) AS party_role,
    COALESCE(( SELECT s.name
           FROM core.sex s
          WHERE (s.id = ccp.sex_id)), 'NA'::text) AS sex,
    COALESCE(( SELECT ct.name
           FROM forensics.crime_type ct
          WHERE (ct.id = ccp.crime_type_id)), 'NA'::text) AS crime_type,
    COALESCE(( SELECT mo.name
           FROM forensics.modus_operandi mo
          WHERE (mo.id = ccp.modus_operandi_id)), 'NA'::text) AS modus_operandi,
    COALESCE(( SELECT md.name
           FROM forensics.mental_disease md
          WHERE (md.id = ccp.mental_disease_id)), 'NA'::text) AS mental_disease,
    COALESCE(( SELECT cm.name
           FROM forensics.crime_motive cm
          WHERE (cm.id = ccp.crime_motive_id)), 'NA'::text) AS crime_motive,
    COALESCE(( SELECT cr.name
           FROM forensics.consultancy_result cr
          WHERE (cr.id = ccp.consultancy_result_id)), 'NA'::text) AS consultancy_result,
    COALESCE(( SELECT j.name
           FROM core.job j
          WHERE (j.id = ccp.job_id)), 'NA'::text) AS job,
    ccp.id AS crime_case_party_id,
    ccp.crime_case_party_role_id,
    ccp.crime_case_id,
    ccp.name AS crime_case_party_role,
    ccp.sex_id,
    ccp.age_in_years,
    ccp.has_precedent_convictions,
    ccp.crime_type_id,
    ccp.modus_operandi_id,
    ccp.mental_disease_id,
    ccp.crime_motive_id,
    ccp.consultancy_result_id,
    ccp.weapon_id,
    ccp.description AS crime_case_party_description,
    ccp.job_id,
    cc.processing_status,
    cc.city,
    cc.housing_type,
    cc.id,
    cc.name,
    cc.city_id,
    cc.housing_type_id,
    cc.crime_year,
    cc.crime_date,
    cc.crime_time,
    cc.description,
    cc.processing_status_id
   FROM (forensics.crime_case_participant ccp
     JOIN all_crime_cases cc ON ((ccp.crime_case_id = cc.id)));


ALTER TABLE crime_case_overview OWNER TO jolo;

--
-- Name: VIEW crime_case_overview; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_overview IS 'overview of all crime cases and all parties involved in crime cases. CAUTION: There is a row for each party involved in a crime case, therefor each crime case appears as many times in the result as there are parties involved!';


--
-- Name: crime_case_party_overview; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW crime_case_party_overview AS
 SELECT COALESCE(( SELECT ccpr.name
           FROM forensics.crime_case_party_role ccpr
          WHERE (ccpr.id = ccp.crime_case_party_role_id)), 'NA'::text) AS party_role,
    COALESCE(( SELECT s.name
           FROM core.sex s
          WHERE (s.id = ccp.sex_id)), 'NA'::text) AS sex,
    COALESCE(( SELECT ct.name
           FROM forensics.crime_type ct
          WHERE (ct.id = ccp.crime_type_id)), 'NA'::text) AS crime_type,
    COALESCE(( SELECT mo.name
           FROM forensics.modus_operandi mo
          WHERE (mo.id = ccp.modus_operandi_id)), 'NA'::text) AS modus_operandi,
    COALESCE(( SELECT md.name
           FROM forensics.mental_disease md
          WHERE (md.id = ccp.mental_disease_id)), 'NA'::text) AS mental_disease,
    COALESCE(( SELECT cm.name
           FROM forensics.crime_motive cm
          WHERE (cm.id = ccp.crime_motive_id)), 'NA'::text) AS crime_motive,
    COALESCE(( SELECT cr.name
           FROM forensics.consultancy_result cr
          WHERE (cr.id = ccp.consultancy_result_id)), 'NA'::text) AS consultancy_result,
    COALESCE(( SELECT j.name
           FROM core.job j
          WHERE (j.id = ccp.job_id)), 'NA'::text) AS job,
    ccp.id,
    ccp.crime_case_party_role_id,
    ccp.crime_case_id,
    ccp.name,
    ccp.sex_id,
    ccp.age_in_years,
    ccp.has_precedent_convictions,
    ccp.crime_type_id,
    ccp.modus_operandi_id,
    ccp.mental_disease_id,
    ccp.crime_motive_id,
    ccp.consultancy_result_id,
    ccp.weapon_id,
    ccp.description,
    ccp.job_id,
    ccp.is_drug_intoxicated,
    ccp.is_alcohol_intoxicated
   FROM forensics.crime_case_participant ccp;


ALTER TABLE crime_case_party_overview OWNER TO jolo;

--
-- Name: VIEW crime_case_party_overview; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW crime_case_party_overview IS 'overview of all parties involved in crime cases';


--
-- Name: drug_intoxications_by_role; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW drug_intoxications_by_role AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(ccp.is_drug_intoxicated) AS is_drug_intoxicated_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR (((ccpr.name = 'Täter'::text) AND (ccp.is_drug_intoxicated = true)) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END
  ORDER BY
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END DESC;


ALTER TABLE drug_intoxications_by_role OWNER TO jolo;

--
-- Name: gebaeudeart_der_faelle; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW gebaeudeart_der_faelle AS
 SELECT
        CASE
            WHEN (ht.name = ''::text) THEN ''::text
            ELSE ht.name
        END AS housing_type_name,
    count(1) AS cnt
   FROM ((forensics.crime_case cc
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN geo.housing_type ht ON (((cc.housing_type_id = ht.id) AND (ps.name <> 'ausgeschlossen'::text))))
  GROUP BY ht.name
  ORDER BY count(1) DESC;


ALTER TABLE gebaeudeart_der_faelle OWNER TO jolo;

--
-- Name: geschlechter_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW geschlechter_der_opfer AS
 SELECT
        CASE
            WHEN (s.name = 'Männlich'::text) THEN 'maschile'::text
            WHEN (s.name = 'Weiblich'::text) THEN 'femminile'::text
            ELSE 'NA'::text
        END AS sex_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN core.sex s ON ((ccp.sex_id = s.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY s.name
  ORDER BY count(1) DESC;


ALTER TABLE geschlechter_der_opfer OWNER TO jolo;

--
-- Name: geschlechter_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW geschlechter_der_taeter AS
 SELECT
        CASE
            WHEN (s.name = 'Männlich'::text) THEN 'maschile'::text
            WHEN (s.name = 'Weiblich'::text) THEN 'femminile'::text
            ELSE 'NA'::text
        END AS sex_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN core.sex s ON ((ccp.sex_id = s.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY s.name
  ORDER BY count(1) DESC;


ALTER TABLE geschlechter_der_taeter OWNER TO jolo;

--
-- Name: modus_operandi_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW modus_operandi_der_opfer AS
 SELECT
        CASE
            WHEN (m.name = ''::text) THEN ''::text
            ELSE m.name
        END AS modus_operandi_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.modus_operandi m ON ((ccp.modus_operandi_id = m.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY m.name
  ORDER BY count(1) DESC;


ALTER TABLE modus_operandi_der_opfer OWNER TO jolo;

--
-- Name: modus_operandi_der_opfer_und_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW modus_operandi_der_opfer_und_taeter AS
 SELECT
        CASE
            WHEN (m.name = ''::text) THEN ''::text
            ELSE m.name
        END AS modus_operandi_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.modus_operandi m ON ((ccp.modus_operandi_id = m.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY m.name
  ORDER BY count(1) DESC;


ALTER TABLE modus_operandi_der_opfer_und_taeter OWNER TO jolo;

--
-- Name: modus_operandi_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW modus_operandi_der_taeter AS
 SELECT
        CASE
            WHEN (m.name = ''::text) THEN ''::text
            ELSE m.name
        END AS modus_operandi_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.modus_operandi m ON ((ccp.modus_operandi_id = m.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY m.name
  ORDER BY count(1) DESC;


ALTER TABLE modus_operandi_der_taeter OWNER TO jolo;

--
-- Name: motive_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW motive_der_opfer AS
 SELECT
        CASE
            WHEN (cm.name = ''::text) THEN ''::text
            ELSE cm.name
        END AS motive_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.crime_motive cm ON ((ccp.crime_motive_id = cm.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY cm.name
  ORDER BY count(1) DESC;


ALTER TABLE motive_der_opfer OWNER TO jolo;

--
-- Name: motive_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW motive_der_taeter AS
 SELECT
        CASE
            WHEN (cm.name = ''::text) THEN ''::text
            ELSE cm.name
        END AS motive_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.crime_motive cm ON ((ccp.crime_motive_id = cm.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY cm.name
  ORDER BY count(1) DESC;


ALTER TABLE motive_der_taeter OWNER TO jolo;

--
-- Name: motive_von_opfern_und_taetern; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW motive_von_opfern_und_taetern AS
 SELECT
        CASE
            WHEN (cm.name = ''::text) THEN ''::text
            ELSE cm.name
        END AS motive_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.crime_motive cm ON ((ccp.crime_motive_id = cm.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY cm.name
  ORDER BY count(1) DESC;


ALTER TABLE motive_von_opfern_und_taetern OWNER TO jolo;

--
-- Name: opfer_per_crime_case_count; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW opfer_per_crime_case_count AS
 SELECT cc.id AS crime_case_id,
    cc.name AS crime_case,
    count(1) AS count
   FROM ((forensics.crime_case cc
     JOIN forensics.crime_case_participant ccp ON ((cc.id = ccp.crime_case_id)))
     JOIN forensics.crime_case_party_role ccpr ON ((ccp.crime_case_party_role_id = ccpr.id)))
  WHERE (ccpr.name = 'Opfer'::text)
  GROUP BY cc.id, cc.name
  ORDER BY cc.id, cc.name, count(1);


ALTER TABLE opfer_per_crime_case_count OWNER TO jolo;

--
-- Name: VIEW opfer_per_crime_case_count; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW opfer_per_crime_case_count IS 'count parties with role <Opfer> involved in crime case';


--
-- Name: parties_by_role_count; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW parties_by_role_count AS
 SELECT cc.id AS crime_case_id,
    cc.name AS crime_case,
    ccpr.name AS crime_case_party_role,
    count(1) AS count
   FROM ((forensics.crime_case cc
     JOIN forensics.crime_case_participant ccp ON ((cc.id = ccp.crime_case_id)))
     JOIN forensics.crime_case_party_role ccpr ON ((ccp.crime_case_party_role_id = ccpr.id)))
  GROUP BY cc.id, cc.name, ccpr.name
  ORDER BY cc.id, cc.name, ccpr.name;


ALTER TABLE parties_by_role_count OWNER TO jolo;

--
-- Name: VIEW parties_by_role_count; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW parties_by_role_count IS 'count parties with their role involved in crime case';


--
-- Name: psychische_erkrankung_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW psychische_erkrankung_der_opfer AS
 SELECT
        CASE
            WHEN (md.name = ''::text) THEN ''::text
            ELSE md.name
        END AS mental_disease_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY md.name
  ORDER BY count(1) DESC;


ALTER TABLE psychische_erkrankung_der_opfer OWNER TO jolo;

--
-- Name: psychische_erkrankung_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW psychische_erkrankung_der_taeter AS
 SELECT
        CASE
            WHEN (md.name = ''::text) THEN ''::text
            ELSE md.name
        END AS mental_disease_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY md.name
  ORDER BY count(1) DESC;


ALTER TABLE psychische_erkrankung_der_taeter OWNER TO jolo;

--
-- Name: staedte_der_faelle; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW staedte_der_faelle AS
 SELECT
        CASE
            WHEN (c.name = ''::text) THEN ''::text
            ELSE c.name
        END AS city_name,
    count(1) AS cnt
   FROM ((forensics.crime_case cc
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN geo.city c ON (((cc.city_id = c.id) AND (ps.name <> 'ausgeschlossen'::text))))
  GROUP BY c.name
  ORDER BY count(1) DESC;


ALTER TABLE staedte_der_faelle OWNER TO jolo;

--
-- Name: taeter_per_crime_case_count; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW taeter_per_crime_case_count AS
 SELECT cc.id AS crime_case_id,
    cc.name AS crime_case,
    count(1) AS count
   FROM ((forensics.crime_case cc
     JOIN forensics.crime_case_participant ccp ON ((cc.id = ccp.crime_case_id)))
     JOIN forensics.crime_case_party_role ccpr ON ((ccp.crime_case_party_role_id = ccpr.id)))
  WHERE (ccpr.name = 'Täter'::text)
  GROUP BY cc.id, cc.name
  ORDER BY cc.id, cc.name, count(1);


ALTER TABLE taeter_per_crime_case_count OWNER TO jolo;

--
-- Name: VIEW taeter_per_crime_case_count; Type: COMMENT; Schema: forstat; Owner: jolo
--

COMMENT ON VIEW taeter_per_crime_case_count IS 'count parties with role <Täter> involved in crime case';


--
-- Name: tatarten_an_opfern; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW tatarten_an_opfern AS
 SELECT
        CASE
            WHEN (ct.name = ''::text) THEN ''::text
            ELSE ct.name
        END AS crime_type_name,
    count(1) AS cnt
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.crime_type ct ON ((ccp.crime_type_id = ct.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY ct.name
  ORDER BY count(1) DESC;


ALTER TABLE tatarten_an_opfern OWNER TO jolo;

--
-- Name: vorbestehende_verurteilungen; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW vorbestehende_verurteilungen AS
 SELECT
        CASE
            WHEN (ccpr.name = 'Täter'::text) THEN 'Attore'::text
            WHEN (ccpr.name = 'Opfer'::text) THEN 'Vittima'::text
            ELSE ccpr.name
        END AS crime_case_party_role_name,
    count(ccp.has_precedent_convictions) AS precedent_conviction_count
   FROM ((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.mental_disease md ON ((ccp.mental_disease_id = md.id)))
  WHERE ((ccpr.name = 'Opfer'::text) OR (((ccpr.name = 'Täter'::text) AND (ccp.has_precedent_convictions = true)) AND (ps.name <> 'ausgeschlossen'::text)))
  GROUP BY ccpr.name
  ORDER BY count(ccp.has_precedent_convictions) DESC;


ALTER TABLE vorbestehende_verurteilungen OWNER TO jolo;

--
-- Name: waffenart_der_opfer; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW waffenart_der_opfer AS
 SELECT
        CASE
            WHEN (wt.name = ''::text) THEN ''::text
            ELSE wt.name
        END AS weapon_type_name,
    count(1) AS cnt
   FROM (((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.weapon w ON ((ccp.weapon_id = w.id)))
     JOIN forensics.weapon_type wt ON ((w.weapon_type_id = wt.id)))
  WHERE ((ccpr.name = 'Opfer'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY wt.name
  ORDER BY count(1) DESC;


ALTER TABLE waffenart_der_opfer OWNER TO jolo;

--
-- Name: waffenart_der_taeter; Type: VIEW; Schema: forstat; Owner: jolo
--

CREATE VIEW waffenart_der_taeter AS
 SELECT
        CASE
            WHEN (wt.name = ''::text) THEN ''::text
            ELSE wt.name
        END AS weapon_type_name,
    count(1) AS cnt
   FROM (((((forensics.crime_case_party_role ccpr
     JOIN forensics.crime_case_participant ccp ON ((ccpr.id = ccp.crime_case_party_role_id)))
     JOIN forensics.crime_case cc ON ((ccp.crime_case_id = cc.id)))
     JOIN core.processing_status ps ON ((cc.processing_status_id = ps.id)))
     JOIN forensics.weapon w ON ((ccp.weapon_id = w.id)))
     JOIN forensics.weapon_type wt ON ((w.weapon_type_id = wt.id)))
  WHERE ((ccpr.name = 'Täter'::text) AND (ps.name <> 'ausgeschlossen'::text))
  GROUP BY wt.name
  ORDER BY count(1) DESC;


ALTER TABLE waffenart_der_taeter OWNER TO jolo;

SET search_path = geo, pg_catalog;

--
-- Name: city_id_seq; Type: SEQUENCE; Schema: geo; Owner: jolo
--

CREATE SEQUENCE city_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE city_id_seq OWNER TO jolo;

--
-- Name: city_id_seq; Type: SEQUENCE OWNED BY; Schema: geo; Owner: jolo
--

ALTER SEQUENCE city_id_seq OWNED BY city.id;


--
-- Name: country_id_seq; Type: SEQUENCE; Schema: geo; Owner: jolo
--

CREATE SEQUENCE country_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE country_id_seq OWNER TO jolo;

--
-- Name: country_id_seq; Type: SEQUENCE OWNED BY; Schema: geo; Owner: jolo
--

ALTER SEQUENCE country_id_seq OWNED BY country.id;


--
-- Name: housing_type_id_seq; Type: SEQUENCE; Schema: geo; Owner: jolo
--

CREATE SEQUENCE housing_type_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE housing_type_id_seq OWNER TO jolo;

--
-- Name: housing_type_id_seq; Type: SEQUENCE OWNED BY; Schema: geo; Owner: jolo
--

ALTER SEQUENCE housing_type_id_seq OWNED BY housing_type.id;


SET search_path = stat, pg_catalog;

--
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
-- Name: altersverteilung; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW altersverteilung AS
 SELECT min(alter_zum_referenzdatum.age) AS minimum,
    max(alter_zum_referenzdatum.age) AS maximum,
    round(avg(alter_zum_referenzdatum.age)) AS durchschnitt
   FROM alter_zum_referenzdatum;


ALTER TABLE altersverteilung OWNER TO jolo;

--
-- Name: VIEW altersverteilung; Type: COMMENT; Schema: stat; Owner: jolo
--

COMMENT ON VIEW altersverteilung IS 'test comment';


--
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
-- Name: probandenalter_und_kampagne; Type: VIEW; Schema: stat; Owner: jolo
--

CREATE VIEW probandenalter_und_kampagne AS
 SELECT alter_zum_referenzdatum.campaign_name AS kampagne,
    alter_zum_referenzdatum.age
   FROM alter_zum_referenzdatum
  ORDER BY alter_zum_referenzdatum.campaign_name, alter_zum_referenzdatum.age;


ALTER TABLE probandenalter_und_kampagne OWNER TO jolo;

--
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
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY administration_method ALTER COLUMN id SET DEFAULT nextval('administration_method_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY age_class ALTER COLUMN id SET DEFAULT nextval('age_class_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY campaign ALTER COLUMN id SET DEFAULT nextval('campaign_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY cgi ALTER COLUMN id SET DEFAULT nextval('cgi_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY channel_into_patient ALTER COLUMN id SET DEFAULT nextval('channel_into_patient_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY collateral_effect ALTER COLUMN id SET DEFAULT nextval('collateral_effect_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY drug ALTER COLUMN id SET DEFAULT nextval('drug_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY fps ALTER COLUMN id SET DEFAULT nextval('fps_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY gaf ALTER COLUMN id SET DEFAULT nextval('gaf_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_diagnosis ALTER COLUMN id SET DEFAULT nextval('icd10_diagnosis_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey ALTER COLUMN id SET DEFAULT nextval('icd10_survey_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY information_source_type ALTER COLUMN id SET DEFAULT nextval('information_source_type_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY job ALTER COLUMN id SET DEFAULT nextval('job_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule ALTER COLUMN id SET DEFAULT nextval('molecule_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule_class ALTER COLUMN id SET DEFAULT nextval('molecule_class_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule_prescription ALTER COLUMN id SET DEFAULT nextval('molecule_prescription_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY organization_unit ALTER COLUMN id SET DEFAULT nextval('organization_unit_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level ALTER COLUMN id SET DEFAULT nextval('plasmatic_level_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug ALTER COLUMN id SET DEFAULT nextval('prescribeable_drug_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition ALTER COLUMN id SET DEFAULT nextval('prescribeable_drug_composition_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY proband ALTER COLUMN id SET DEFAULT nextval('proband_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY processing_status ALTER COLUMN id SET DEFAULT nextval('processing_status_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY project ALTER COLUMN id SET DEFAULT nextval('project_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY sex ALTER COLUMN id SET DEFAULT nextval('sex_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY smoking_habit ALTER COLUMN id SET DEFAULT nextval('smoking_habit_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey ALTER COLUMN id SET DEFAULT nextval('survey_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect ALTER COLUMN id SET DEFAULT nextval('survey_collateral_effect_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_info ALTER COLUMN id SET DEFAULT nextval('survey_info_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY unit ALTER COLUMN id SET DEFAULT nextval('unit_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY who_qol ALTER COLUMN id SET DEFAULT nextval('who_qol_id_seq'::regclass);


SET search_path = forensics, pg_catalog;

--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY consultancy_result ALTER COLUMN id SET DEFAULT nextval('consultancy_result_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case ALTER COLUMN id SET DEFAULT nextval('crime_case_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant ALTER COLUMN id SET DEFAULT nextval('crime_case_participant_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_party_role ALTER COLUMN id SET DEFAULT nextval('crime_case_party_role_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_motive ALTER COLUMN id SET DEFAULT nextval('crime_motive_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_type ALTER COLUMN id SET DEFAULT nextval('crime_type_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY information_source_for_crime_case ALTER COLUMN id SET DEFAULT nextval('information_source_for_crime_case_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY mental_disease ALTER COLUMN id SET DEFAULT nextval('mental_disease_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY modus_operandi ALTER COLUMN id SET DEFAULT nextval('modus_operandi_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY weapon ALTER COLUMN id SET DEFAULT nextval('weapon_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY weapon_type ALTER COLUMN id SET DEFAULT nextval('weapon_type_id_seq'::regclass);


SET search_path = geo, pg_catalog;

--
-- Name: id; Type: DEFAULT; Schema: geo; Owner: jolo
--

ALTER TABLE ONLY city ALTER COLUMN id SET DEFAULT nextval('city_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: geo; Owner: jolo
--

ALTER TABLE ONLY country ALTER COLUMN id SET DEFAULT nextval('country_id_seq'::regclass);


--
-- Name: id; Type: DEFAULT; Schema: geo; Owner: jolo
--

ALTER TABLE ONLY housing_type ALTER COLUMN id SET DEFAULT nextval('housing_type_id_seq'::regclass);


SET search_path = core, pg_catalog;

--
-- Name: administration_method_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_name_key UNIQUE (name);


--
-- Name: administration_method_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_pkey PRIMARY KEY (id);


--
-- Name: age_class_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY age_class
    ADD CONSTRAINT age_class_name_key UNIQUE (name);


--
-- Name: age_class_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY age_class
    ADD CONSTRAINT age_class_pkey PRIMARY KEY (id);


--
-- Name: campaign_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_name_key UNIQUE (name);


--
-- Name: campaign_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_pkey PRIMARY KEY (id);


--
-- Name: campaign_project_id_start_date_end_date_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_project_id_start_date_end_date_key UNIQUE (project_id, start_date, end_date);


--
-- Name: cgi_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_pkey PRIMARY KEY (id);


--
-- Name: cgi_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_survey_id_key UNIQUE (survey_id);


--
-- Name: channel_into_patient_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY channel_into_patient
    ADD CONSTRAINT channel_into_patient_name_key UNIQUE (name);


--
-- Name: channel_into_patient_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY channel_into_patient
    ADD CONSTRAINT channel_into_patient_pkey PRIMARY KEY (id);


--
-- Name: collateral_effect_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY collateral_effect
    ADD CONSTRAINT collateral_effect_name_key UNIQUE (name);


--
-- Name: collateral_effect_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY collateral_effect
    ADD CONSTRAINT collateral_effect_pkey PRIMARY KEY (id);


--
-- Name: depot_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_pkey PRIMARY KEY (id);


--
-- Name: depot_prescription_survey_id_prescribeable_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_survey_id_prescribeable_drug_id_key UNIQUE (survey_id, prescribeable_drug_id);


--
-- Name: drug_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY drug
    ADD CONSTRAINT drug_name_key UNIQUE (name);


--
-- Name: drug_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY drug
    ADD CONSTRAINT drug_pkey PRIMARY KEY (id);


--
-- Name: fps_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_pkey PRIMARY KEY (id);


--
-- Name: fps_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_survey_id_key UNIQUE (survey_id);


--
-- Name: gaf_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_pkey PRIMARY KEY (id);


--
-- Name: gaf_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_survey_id_key UNIQUE (survey_id);


--
-- Name: icd10_diagnosis_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_diagnosis
    ADD CONSTRAINT icd10_diagnosis_name_key UNIQUE (name);


--
-- Name: icd10_diagnosis_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_diagnosis
    ADD CONSTRAINT icd10_diagnosis_pkey PRIMARY KEY (id);


--
-- Name: icd10_survey_icd10_diagnosis_id_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_icd10_diagnosis_id_survey_id_key UNIQUE (icd10_diagnosis_id, survey_id);


--
-- Name: information_source_type_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY information_source_type
    ADD CONSTRAINT information_source_type_name_key UNIQUE (name);


--
-- Name: information_source_type_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY information_source_type
    ADD CONSTRAINT information_source_type_pkey PRIMARY KEY (id);


--
-- Name: job_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY job
    ADD CONSTRAINT job_name_key UNIQUE (name);


--
-- Name: job_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY job
    ADD CONSTRAINT job_pkey PRIMARY KEY (id);


--
-- Name: molecule_class_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_class
    ADD CONSTRAINT molecule_class_name_key UNIQUE (name);


--
-- Name: molecule_class_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_class
    ADD CONSTRAINT molecule_class_pkey PRIMARY KEY (id);


--
-- Name: molecule_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_name_key UNIQUE (name);


--
-- Name: molecule_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_pkey PRIMARY KEY (id);


--
-- Name: molecule_prescription_molecule_id_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_prescription
    ADD CONSTRAINT molecule_prescription_molecule_id_survey_id_key UNIQUE (molecule_id, survey_id);


--
-- Name: molecule_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY molecule_prescription
    ADD CONSTRAINT molecule_prescription_pkey PRIMARY KEY (id);


--
-- Name: optional_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_pkey PRIMARY KEY (id);


--
-- Name: optional_prescription_survey_id_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_survey_id_drug_id_key UNIQUE (survey_id, drug_id);


--
-- Name: organization_unit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY organization_unit
    ADD CONSTRAINT organization_unit_name_key UNIQUE (name);


--
-- Name: organization_unit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY organization_unit
    ADD CONSTRAINT organization_unit_pkey PRIMARY KEY (id);


--
-- Name: pk_icd10_survey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT pk_icd10_survey PRIMARY KEY (id);


--
-- Name: plasmatic_level_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_pkey PRIMARY KEY (id);


--
-- Name: prescribeable_drug_compositio_prescribeable_drug_id_molecul_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_compositio_prescribeable_drug_id_molecul_key UNIQUE (prescribeable_drug_id, molecule_id);


--
-- Name: prescribeable_drug_composition_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_pkey PRIMARY KEY (id);


--
-- Name: prescribeable_drug_dosage_dosage_unit_id_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_dosage_dosage_unit_id_drug_id_key UNIQUE (dosage, dosage_unit_id, drug_id);


--
-- Name: prescribeable_drug_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_name_key UNIQUE (name);


--
-- Name: prescribeable_drug_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_pkey PRIMARY KEY (id);


--
-- Name: proband_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY proband
    ADD CONSTRAINT proband_pkey PRIMARY KEY (id);


--
-- Name: processing_status_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY processing_status
    ADD CONSTRAINT processing_status_name_key UNIQUE (name);


--
-- Name: processing_status_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY processing_status
    ADD CONSTRAINT processing_status_pkey PRIMARY KEY (id);


--
-- Name: project_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY project
    ADD CONSTRAINT project_name_key UNIQUE (name);


--
-- Name: project_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY project
    ADD CONSTRAINT project_pkey PRIMARY KEY (id);


--
-- Name: regular_prescription_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_pkey PRIMARY KEY (id);


--
-- Name: regular_prescription_survey_id_prescribeable_drug_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_survey_id_prescribeable_drug_id_key UNIQUE (survey_id, prescribeable_drug_id);


--
-- Name: sex_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY sex
    ADD CONSTRAINT sex_name_key UNIQUE (name);


--
-- Name: sex_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY sex
    ADD CONSTRAINT sex_pkey PRIMARY KEY (id);


--
-- Name: smoking_habit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY smoking_habit
    ADD CONSTRAINT smoking_habit_name_key UNIQUE (name);


--
-- Name: smoking_habit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY smoking_habit
    ADD CONSTRAINT smoking_habit_pkey PRIMARY KEY (id);


--
-- Name: survey_collateral_effect_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_pkey PRIMARY KEY (id);


--
-- Name: survey_info_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey_info
    ADD CONSTRAINT survey_info_pkey PRIMARY KEY (id);


--
-- Name: survey_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_pkey PRIMARY KEY (id);


--
-- Name: survey_proband_id_campaign_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_proband_id_campaign_id_key UNIQUE (proband_id, campaign_id);


--
-- Name: unit_name_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY unit
    ADD CONSTRAINT unit_name_key UNIQUE (name);


--
-- Name: unit_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY unit
    ADD CONSTRAINT unit_pkey PRIMARY KEY (id);


--
-- Name: who_qol_pkey; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_pkey PRIMARY KEY (id);


--
-- Name: who_qol_survey_id_key; Type: CONSTRAINT; Schema: core; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_survey_id_key UNIQUE (survey_id);


SET search_path = forensics, pg_catalog;

--
-- Name: consultancy_result_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY consultancy_result
    ADD CONSTRAINT consultancy_result_name_key UNIQUE (name);


--
-- Name: consultancy_result_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY consultancy_result
    ADD CONSTRAINT consultancy_result_pkey PRIMARY KEY (id);


--
-- Name: crime_case_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_case
    ADD CONSTRAINT crime_case_name_key UNIQUE (name);


--
-- Name: crime_case_participant_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_pkey PRIMARY KEY (id);


--
-- Name: crime_case_party_role_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_case_party_role
    ADD CONSTRAINT crime_case_party_role_name_key UNIQUE (name);


--
-- Name: crime_case_party_role_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_case_party_role
    ADD CONSTRAINT crime_case_party_role_pkey PRIMARY KEY (id);


--
-- Name: crime_case_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_case
    ADD CONSTRAINT crime_case_pkey PRIMARY KEY (id);


--
-- Name: crime_motive_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_motive
    ADD CONSTRAINT crime_motive_name_key UNIQUE (name);


--
-- Name: crime_motive_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_motive
    ADD CONSTRAINT crime_motive_pkey PRIMARY KEY (id);


--
-- Name: crime_type_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_type
    ADD CONSTRAINT crime_type_name_key UNIQUE (name);


--
-- Name: crime_type_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY crime_type
    ADD CONSTRAINT crime_type_pkey PRIMARY KEY (id);


--
-- Name: information_source_for_crime_case_crime_case_id_url_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY information_source_for_crime_case
    ADD CONSTRAINT information_source_for_crime_case_crime_case_id_url_key UNIQUE (crime_case_id, url);


--
-- Name: information_source_for_crime_case_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY information_source_for_crime_case
    ADD CONSTRAINT information_source_for_crime_case_pkey PRIMARY KEY (id);


--
-- Name: mental_disease_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY mental_disease
    ADD CONSTRAINT mental_disease_name_key UNIQUE (name);


--
-- Name: mental_disease_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY mental_disease
    ADD CONSTRAINT mental_disease_pkey PRIMARY KEY (id);


--
-- Name: modus_operandi_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY modus_operandi
    ADD CONSTRAINT modus_operandi_name_key UNIQUE (name);


--
-- Name: modus_operandi_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY modus_operandi
    ADD CONSTRAINT modus_operandi_pkey PRIMARY KEY (id);


--
-- Name: weapon_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY weapon
    ADD CONSTRAINT weapon_name_key UNIQUE (name);


--
-- Name: weapon_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY weapon
    ADD CONSTRAINT weapon_pkey PRIMARY KEY (id);


--
-- Name: weapon_type_name_key; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY weapon_type
    ADD CONSTRAINT weapon_type_name_key UNIQUE (name);


--
-- Name: weapon_type_pkey; Type: CONSTRAINT; Schema: forensics; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY weapon_type
    ADD CONSTRAINT weapon_type_pkey PRIMARY KEY (id);


SET search_path = geo, pg_catalog;

--
-- Name: city_name_key; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY city
    ADD CONSTRAINT city_name_key UNIQUE (name);


--
-- Name: city_pkey; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY city
    ADD CONSTRAINT city_pkey PRIMARY KEY (id);


--
-- Name: country_name_key; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY country
    ADD CONSTRAINT country_name_key UNIQUE (name);


--
-- Name: country_pkey; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY country
    ADD CONSTRAINT country_pkey PRIMARY KEY (id);


--
-- Name: country_symbol_key; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY country
    ADD CONSTRAINT country_symbol_key UNIQUE (symbol);


--
-- Name: housing_type_name_key; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY housing_type
    ADD CONSTRAINT housing_type_name_key UNIQUE (name);


--
-- Name: housing_type_pkey; Type: CONSTRAINT; Schema: geo; Owner: jolo; Tablespace: 
--

ALTER TABLE ONLY housing_type
    ADD CONSTRAINT housing_type_pkey PRIMARY KEY (id);


SET search_path = core, pg_catalog;

--
-- Name: administration_method_channel_into_patient_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY administration_method
    ADD CONSTRAINT administration_method_channel_into_patient_id_fkey FOREIGN KEY (channel_into_patient_id) REFERENCES channel_into_patient(id);


--
-- Name: campaign_project_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY campaign
    ADD CONSTRAINT campaign_project_id_fkey FOREIGN KEY (project_id) REFERENCES project(id);


--
-- Name: cgi_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY cgi
    ADD CONSTRAINT cgi_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: depot_prescription_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- Name: depot_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY depot_prescription
    ADD CONSTRAINT depot_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: fps_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY fps
    ADD CONSTRAINT fps_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: gaf_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY gaf
    ADD CONSTRAINT gaf_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: icd10_survey_icd10_diagnosis_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_icd10_diagnosis_id_fkey FOREIGN KEY (icd10_diagnosis_id) REFERENCES icd10_diagnosis(id);


--
-- Name: icd10_survey_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY icd10_survey
    ADD CONSTRAINT icd10_survey_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: molecule_molecule_class_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule
    ADD CONSTRAINT molecule_molecule_class_id_fkey FOREIGN KEY (molecule_class_id) REFERENCES molecule_class(id);


--
-- Name: molecule_prescription_molecule_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule_prescription
    ADD CONSTRAINT molecule_prescription_molecule_id_fkey FOREIGN KEY (molecule_id) REFERENCES molecule(id);


--
-- Name: molecule_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY molecule_prescription
    ADD CONSTRAINT molecule_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: optional_prescription_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_drug_id_fkey FOREIGN KEY (drug_id) REFERENCES drug(id);


--
-- Name: optional_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY optional_prescription
    ADD CONSTRAINT optional_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: plasmatic_level_molecule_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_molecule_id_fkey FOREIGN KEY (molecule_id) REFERENCES molecule(id);


--
-- Name: plasmatic_level_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: plasmatic_level_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY plasmatic_level
    ADD CONSTRAINT plasmatic_level_unit_id_fkey FOREIGN KEY (unit_id) REFERENCES unit(id);


--
-- Name: prescribeable_drug_administration_method_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_administration_method_id_fkey FOREIGN KEY (administration_method_id) REFERENCES administration_method(id);


--
-- Name: prescribeable_drug_composition_amount_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_amount_unit_id_fkey FOREIGN KEY (amount_unit_id) REFERENCES unit(id);


--
-- Name: prescribeable_drug_composition_molecule_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_molecule_id_fkey FOREIGN KEY (molecule_id) REFERENCES molecule(id);


--
-- Name: prescribeable_drug_composition_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug_composition
    ADD CONSTRAINT prescribeable_drug_composition_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- Name: prescribeable_drug_dosage_unit_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_dosage_unit_id_fkey FOREIGN KEY (dosage_unit_id) REFERENCES unit(id);


--
-- Name: prescribeable_drug_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY prescribeable_drug
    ADD CONSTRAINT prescribeable_drug_drug_id_fkey FOREIGN KEY (drug_id) REFERENCES drug(id);


--
-- Name: proband_sex_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY proband
    ADD CONSTRAINT proband_sex_id_fkey FOREIGN KEY (sex_id) REFERENCES sex(id);


--
-- Name: regular_prescription_prescribeable_drug_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_prescribeable_drug_id_fkey FOREIGN KEY (prescribeable_drug_id) REFERENCES prescribeable_drug(id);


--
-- Name: regular_prescription_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY regular_prescription
    ADD CONSTRAINT regular_prescription_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: survey_campaign_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_campaign_id_fkey FOREIGN KEY (campaign_id) REFERENCES campaign(id);


--
-- Name: survey_collateral_effect_collateral_effect_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_collateral_effect_id_fkey FOREIGN KEY (collateral_effect_id) REFERENCES collateral_effect(id);


--
-- Name: survey_collateral_effect_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_collateral_effect
    ADD CONSTRAINT survey_collateral_effect_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: survey_info_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey_info
    ADD CONSTRAINT survey_info_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


--
-- Name: survey_proband_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY survey
    ADD CONSTRAINT survey_proband_id_fkey FOREIGN KEY (proband_id) REFERENCES proband(id);


--
-- Name: who_qol_survey_id_fkey; Type: FK CONSTRAINT; Schema: core; Owner: jolo
--

ALTER TABLE ONLY who_qol
    ADD CONSTRAINT who_qol_survey_id_fkey FOREIGN KEY (survey_id) REFERENCES survey(id);


SET search_path = forensics, pg_catalog;

--
-- Name: crime_case_city_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case
    ADD CONSTRAINT crime_case_city_id_fkey FOREIGN KEY (city_id) REFERENCES geo.city(id);


--
-- Name: crime_case_housing_type_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case
    ADD CONSTRAINT crime_case_housing_type_id_fkey FOREIGN KEY (housing_type_id) REFERENCES geo.housing_type(id);


--
-- Name: crime_case_participant_consultancy_result_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_consultancy_result_id_fkey FOREIGN KEY (consultancy_result_id) REFERENCES consultancy_result(id);


--
-- Name: crime_case_participant_crime_case_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_crime_case_id_fkey FOREIGN KEY (crime_case_id) REFERENCES crime_case(id);


--
-- Name: crime_case_participant_crime_case_party_role_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_crime_case_party_role_id_fkey FOREIGN KEY (crime_case_party_role_id) REFERENCES crime_case_party_role(id);


--
-- Name: crime_case_participant_crime_motive_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_crime_motive_id_fkey FOREIGN KEY (crime_motive_id) REFERENCES crime_motive(id);


--
-- Name: crime_case_participant_crime_type_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_crime_type_id_fkey FOREIGN KEY (crime_type_id) REFERENCES crime_type(id);


--
-- Name: crime_case_participant_mental_disease_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_mental_disease_id_fkey FOREIGN KEY (mental_disease_id) REFERENCES mental_disease(id);


--
-- Name: crime_case_participant_modus_operandi_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_modus_operandi_id_fkey FOREIGN KEY (modus_operandi_id) REFERENCES modus_operandi(id);


--
-- Name: crime_case_participant_sex_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_sex_id_fkey FOREIGN KEY (sex_id) REFERENCES core.sex(id);


--
-- Name: crime_case_participant_weapon_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT crime_case_participant_weapon_id_fkey FOREIGN KEY (weapon_id) REFERENCES weapon(id);


--
-- Name: fk_job; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case_participant
    ADD CONSTRAINT fk_job FOREIGN KEY (job_id) REFERENCES core.job(id);


--
-- Name: fk_status; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY crime_case
    ADD CONSTRAINT fk_status FOREIGN KEY (processing_status_id) REFERENCES core.processing_status(id);


--
-- Name: information_source_for_crime_ca_information_source_type_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY information_source_for_crime_case
    ADD CONSTRAINT information_source_for_crime_ca_information_source_type_id_fkey FOREIGN KEY (information_source_type_id) REFERENCES core.information_source_type(id);


--
-- Name: information_source_for_crime_case_crime_case_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY information_source_for_crime_case
    ADD CONSTRAINT information_source_for_crime_case_crime_case_id_fkey FOREIGN KEY (crime_case_id) REFERENCES crime_case(id);


--
-- Name: weapon_weapon_type_id_fkey; Type: FK CONSTRAINT; Schema: forensics; Owner: jolo
--

ALTER TABLE ONLY weapon
    ADD CONSTRAINT weapon_weapon_type_id_fkey FOREIGN KEY (weapon_type_id) REFERENCES weapon_type(id);


SET search_path = geo, pg_catalog;

--
-- Name: city_country_id_fkey; Type: FK CONSTRAINT; Schema: geo; Owner: jolo
--

ALTER TABLE ONLY city
    ADD CONSTRAINT city_country_id_fkey FOREIGN KEY (country_id) REFERENCES country(id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

